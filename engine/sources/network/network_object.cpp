#include "network/network_object.hpp"
#include "network/network.hpp"
#include "network/objects_protocol.hpp"

std::unordered_map<std::string,NetworkObjectsDB::ObjectCreator> NetworkObjectsDB::m_objects;

NetworkObjectsDB::ObjectCreator NetworkObjectsDB::creator(const std::string &class_name){
    return m_objects.find(class_name)->second;
}


void NetworkObject::_on_introduce(){
    
    if(originator){
        Network::client()->obj_create(this);
        Info(network_class()+"::_on_introduce()");
    }
}
void NetworkObject::_on_destroy(){
    Network::client()->obj_destory(this);
    Info(network_class()+"::_on_destroy()");
}

NetworkObject::NetworkObject():
    m_guid(),
    originator(true)
{ 
    
}

NetworkObject::NetworkObject(const GUID &guid):
    m_guid(guid),
    originator(false)
{ }


std::string NetworkObject::static_network_class(){  
    return std::string("NetworkObject");              
}                                           
std::string NetworkObject::network_class(){        
    return std::string("NetworkObject");              
}
const GUID &NetworkObject::guid()const{
    return m_guid;
}

NetworkObject *NetworkObject::set_guid(const GUID &guid){
    m_guid = guid;
    return this;
}