#include "network/network_object.hpp"
#include "network/objects_protocol.hpp"
#include "network/network_scene.hpp"
#include "engine.hpp"
#include "core/math/math.hpp"
std::unordered_map<std::string,NetworkObjectsDB::ObjectCreator> NetworkObjectsDB::m_objects;

NetworkObjectsDB::ObjectCreator NetworkObjectsDB::creator(const std::string &class_name){
    ASSERT_ERROR(m_objects.find(class_name)!=m_objects.end(),"NetworkObjectDB: unregistered object: " + class_name);
    return m_objects.find(class_name)->second;
}


void NetworkObject::_on_update(float dt){
    m_timer+=dt;
    
    if(m_network_dirty && (Math::length(m_network_offset)>10 || m_timer > 0.01f)){
        ASSERT_ERROR(m_type==NetworkObject::Type::Originator,"Can't sync imitator transform");
        network_sync_transform();
    }
}


void NetworkObject::on_network_translate(const sf::Vector2f &local_position){
    ASSERT_ERROR(m_type==NetworkObject::Type::Originator,"Can't transform imitator");
    set_local_position(local_position);
}

NetworkObject::NetworkObject():
    m_guid(),
    m_type(NetworkObject::Type::Originator),
    m_timer(0),
    m_network_offset(0,0),
    m_network_dirty(false)
{ 
    
}

NetworkObject::NetworkObject(const GUID &guid):
    m_guid(guid),
    m_type(NetworkObject::Type::Imitator),
    m_network_dirty(false)
{ 
}


void NetworkObject::network_translate(const sf::Vector2f &offset){
    translate(offset);
    m_network_offset+=offset;
    m_network_dirty = true;
}
void NetworkObject::network_translate(float x_offset, float y_offset){
    network_translate(sf::Vector2f(x_offset,y_offset));
}
void NetworkObject::network_sync_transform(){
    EventObjectTranslate e;
    e.guid=m_guid;
    e.position=local_position();
    static_cast<NetworkScene*>(scene())->send(&e,sizeof(e));

    m_timer = 0;
    m_network_dirty = false;
    m_network_offset = sf::Vector2f(0,0);
}

void NetworkObject::network_event(const Event &e){
    static_cast<NetworkScene*>(scene())->event(e);
}

NetworkObject *NetworkObject::network_object_introduce(NetworkObject *object){
    scene()->network_object_introduce(object);
    return object;
}

void NetworkObject::destroy(){
    static_cast<NetworkScene*>(scene())->network_object_substract(this);
}

void NetworkObject::originator_event(const OriginatorEvent &e){
    EventObjectOriginator event;
    event.type = protocol::DatagramType::Event;
    event.code.event = EventCode(Events::ObjectOriginatorEvent);
    event.guid = m_guid;
    event.content = e;
    static_cast<NetworkScene*>(scene())->send(&event,sizeof(EventObjectOriginator));
}
void NetworkObject::on_originator_event(const OriginatorEvent &e){
    Info("NetworkObject: originator event callback is not implemented");
}

std::string NetworkObject::static_network_class(){  
    return std::string("NetworkObject");              
}                                           
std::string NetworkObject::network_class(){        
    return std::string("NetworkObject");              
}

NetworkObject::Type NetworkObject::type(){
    return m_type;
}

NetworkObject *NetworkObject::set_guid(const GUID &guid){
    m_guid = guid;
    return this;
}
const GUID &NetworkObject::guid()const{
    return m_guid;
}
