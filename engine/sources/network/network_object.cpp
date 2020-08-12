#include "network/network_object.hpp"
#include "network/network.hpp"
#include "network/objects_protocol.hpp"

std::unordered_map<std::string,NetworkObjectsDB::ObjectCreator> NetworkObjectsDB::m_objects;

NetworkObjectsDB::ObjectCreator NetworkObjectsDB::creator(const std::string &class_name){
    return m_objects.find(class_name)->second;
}


NetworkObject::NetworkObject():
    m_guid(),
    originator(true)
{ 
    Network::client()->obj_create(this);
}

NetworkObject::NetworkObject(const GUID &guid):
    m_guid(guid),
    originator(false)
{ }

NetworkObject::~NetworkObject()
{
    //if(introduced())
    Network::client()->obj_destory(this);
}
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