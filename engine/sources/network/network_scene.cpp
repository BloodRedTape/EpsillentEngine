#include "network/network_scene.hpp"
#include "string.h"
#include "SFML/Network/Packet.hpp"
#include "scenes/scene_manager.hpp"
NetworkScene::NetworkScene(){

}
NetworkScene::~NetworkScene(){
    scene_graph.clear();
    clear_garbage();
    if(is_connected())
        disconnect();
}

void NetworkScene::update(const float dt){
    scene_graph.update(dt);
    scene_cluster.update(dt);
    if(is_connected())
        fetch();
}

void NetworkScene::event(const Event &e){
    ASSERT_WARRNING(is_connected(),"Netowork: Can not send and Event: Scene is not connected");
    send(const_cast<Event*>(&e),sizeof(e));
}
void NetworkScene::fetch() {
    sf::Packet datagram;
    Host sender;
    std::size_t size;
    auto status = socket.receive(datagram, sender.ip, sender.port);
    if (status == sf::Socket::Status::Done || status == sf::Socket::Status::Partial) {
        if (*(protocol::DatagramType*)datagram.getData() == protocol::DatagramType::Event) {
            handle_event(datagram);
        }
        else {
            Info("Network: unintended datagram recieved");
        }
    }
}
//event handling based on a switch because it is stupid
//to use dispatch table for three fucking options
//probably there will be one but only if we have 
//more than ten Scene-Handled events
void NetworkScene::handle_event(const sf::Packet &packet){
    protocol::Header& header = *(protocol::Header*)packet.getData();
    switch ((Events)header.code.event)
    {
    case Events::ObjectOriginatorEvent:
        on_object_originator_event(packet);
        break;
    case Events::ObjectNew:
        on_object_new(packet);
        break;
    case Events::ObjectDelete:
        on_object_delete(packet);
        break;
    case Events::ObjectTranslate:
        on_object_translate(packet);
        break;
    default:
        Info("Network: unknown Event");
        break;
    }
}

void NetworkScene::object_new(NetworkObject *object){
    EventObjectNew e;
    e.guid = object->m_guid;
    e.position = object->local_position();
    std::string name = object->network_class();
    memcpy(e.class_name,name.c_str(),name.size()+1);
    Info("Network: new object " + name + " size " + std::to_string(name.size()));
    ASSERT_ERROR(name.size()<=(sizeof(e.class_name)/sizeof(e.class_name[0])),"Network: object class name is too big");
    send(&e,sizeof(e));
    objects.emplace(object->guid(),object);
}
void NetworkScene::object_delete(NetworkObject *object){
    if(object->m_type == NetworkObject::Type::Originator){
        EventObjectDelete e;
        e.guid = object->m_guid;
        send(&e,sizeof(e));
        Info("Network: deleted object " + object->network_class());
    }
    objects.erase(object->m_guid);
}
void NetworkScene::on_object_new(const sf::Packet &packet){
    EventObjectNew& event = *(EventObjectNew*)packet.getData();
    Info("Network: Event: new remote object " + std::string(event.class_name) + " " + std::string(event.guid) + ARG_VEC("POsition",event.position));
    NetworkObject *object = (*NetworkObjectsDB::creator(event.class_name))(this,event.guid);
    object->on_network_translate(event.position);
    objects.emplace(event.guid,object);
}
void NetworkScene::on_object_delete(const sf::Packet &packet){
    EventObjectDelete& event = *(EventObjectDelete*)packet.getData();
    Info("Network: Event: delete remote object " + std::string(event.guid));
    auto object = objects.find(event.guid);
    if(object==objects.end()){
        Warning("Network: can not delete " + std::string(event.guid)+ " object does not exits");
        return;
    }
    object->second->destroy();
}
void NetworkScene::on_object_originator_event(const sf::Packet &packet){
    EventObjectOriginator &event = *(EventObjectOriginator*)packet.getData();
    auto object = objects.find(event.guid);
    if(object==objects.end()){
        Warning("Network: can't find an object" + std::string(event.guid)+" for event handling");
        return;
    }
    objects.find(event.guid)->second->on_originator_event(event.content);
}


void NetworkScene::on_object_translate(const sf::Packet &packet){
    EventObjectTranslate& event = *(EventObjectTranslate*)packet.getData();
    auto object = objects.find(event.guid);
    if(object==objects.end()){
        Warning("Network: can't find an object" + std::string(event.guid)+" for translate event handling");
        return;
    }
    objects.find(event.guid)->second->on_network_translate(event.position);
}