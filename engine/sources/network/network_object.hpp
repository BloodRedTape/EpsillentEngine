#ifndef NETWORK_OBJECT_H
#define NETWORK_OBJECT_H


#include <unordered_map>
#include "config/config.hpp"
#include "core/guid.hpp"
#include "scenes/scene.hpp"
#include "utils/debug.hpp"

class NetworkObject;

#define NETWORK_CLASS(Name,Inherited)           \
public:                                         \
    static std::string static_network_class(){  \
        return std::string(#Name);              \
    }                                           \
    virtual std::string network_class(){        \
        return std::string(#Name);              \
    }                                           \
    Name(const GUID& guid): Inherited(guid) {}  \
private:

class NetworkObjectsDB{
private:
    typedef void (*ObjectCreator)(BaseScene*,const GUID &);
    static std::unordered_map<std::string,ObjectCreator> m_objects;

public:
    template <typename T>
    static void _obj_creator(BaseScene *scene, const GUID &guid){
        scene->object_introduce(new T(guid));
    }
    template <typename T>
    static void register_object(){
        m_objects.emplace(T::static_network_class(),&NetworkObjectsDB::_obj_creator<T>);
    }
    ObjectCreator creator(const std::string &class_name);
};


class NetworkObject: public GameObject{
private:
    bool originator;
    GUID m_guid;
public:
    NetworkObject();
    NetworkObject(const GUID &guid);
    virtual ~NetworkObject();

    NetworkObject *set_guid(const GUID &);
    static std::string static_network_class(){  
        return std::string("NetworkObject");              
    }                                           
    virtual std::string network_class(){        
        return std::string("NetworkObject");              
    }                                          
};

#endif