#include "network/network_scene.hpp"
#include "string.h"
NetworkScene::NetworkScene(){

}
NetworkScene::~NetworkScene(){
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
void NetworkScene::fetch(){
    Datagram datagram;
    Host sender;
    std::size_t size;
    if(socket.receive(&datagram,sizeof(Datagram),size,sender.ip,sender.port)==sf::Socket::Done){
        if(datagram.type == protocol::DatagramType::Event){
            handle_event((Event)datagram);
        }else{
            Info("Network: unintended datagram recieved");
        }
    }
}

//event handling based on a switch because it is stupid
//to use dispatch table for three fucking options
//probably there will be one but only if we have 
//more than ten Scene-Handled events
void NetworkScene::handle_event(const Event &e){
    EventObjectNew &event = *(EventObjectNew*)&e;
    switch ((Events)e.code.event)
    {
    case Events::ObjectOriginatorEvent:
        on_object_originator_event(e);
        break;
    case Events::ObjectNew:
        on_object_new(event.guid,event.position,event.class_name);
        break;
    case Events::ObjectDelete:
        on_object_delete(*(GUID*)e.data);
        break;
    case Events::ObjectVar:
        on_object_var(*(GUID*)e.data,e);
        break;
    case Events::ObjectTranslate:
        on_object_translate(*(GUID*)e.data,e);
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
        Info("Network: new object " + object->network_class());
    }
    objects.erase(object->m_guid);
}
void NetworkScene::on_object_new(const GUID &guid,const sf::Vector2f &position, const std::string &class_name){
    Info("Network: Event: new remote object " + class_name + " " + std::string(guid) + ARG_VEC("POsition",position));
    NetworkObject *object = (*NetworkObjectsDB::creator(class_name))(this,guid);
    object->translate(position);
    objects.emplace(guid,object);
}
void NetworkScene::on_object_delete(const GUID &guid){
    Info("Network: Event: delete remote object " + std::string(guid));
    auto object = objects.find(guid);
    if(object==objects.end()){
        Warning("Network: can not delete " + std::string(guid)+ " object does not exits");
        return;
    }
    object->second->destroy();
}
void NetworkScene::on_object_originator_event(const Event &e){
    EventObjectOriginator &event = *(EventObjectOriginator*)&e;
    auto object = objects.find(event.guid);
    if(object==objects.end()){
        Warning("Network: can't find an object" + std::string(event.guid)+" for event handling");
        return;
    }
    objects.find(event.guid)->second->on_originator_event(event.content);
}

void NetworkScene::on_object_var(const GUID &guid, const Event &e){
    auto object = objects.find(guid);
    if(object==objects.end()){
        Warning("Network: can't find an object" + std::string(guid)+" for variable event handling");
        return;
    }
    objects.find(guid)->second->on_network_variable(e);
}
void NetworkScene::on_object_translate(const GUID &guid, const Event &e){
    auto object = objects.find(guid);
    if(object==objects.end()){
        Warning("Network: can't find an object" + std::string(guid)+" for translate event handling");
        return;
    }
    objects.find(guid)->second->on_network_translate(e);
}