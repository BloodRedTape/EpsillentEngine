#include "network/network_object.hpp"


std::unordered_map<std::string,NetworkObjectsDB::ObjectCreator> NetworkObjectsDB::m_objects;

NetworkObjectsDB::ObjectCreator NetworkObjectsDB::creator(const std::string &class_name){
    return m_objects.find(class_name)->second;
}

NetworkObject::NetworkObject():
    m_guid(),
    originator(false)
{}

NetworkObject::NetworkObject(const GUID &guid):
    m_guid(guid),
    originator(true)
{
    // send creation request
}

NetworkObject::~NetworkObject()
{
    if(originator)
        ;// send death request;
}


NetworkObject *NetworkObject::set_guid(const GUID &guid){
    m_guid = guid;
    return this;
}