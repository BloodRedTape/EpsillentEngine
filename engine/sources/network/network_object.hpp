#ifndef NETWORK_OBJECT_H
#define NETWORK_OBJECT_H


#include <unordered_map>
#include "config/config.hpp"
#include "core/guid.hpp"
#include "core/net/protocol.hpp"
#include "scenes/scene.hpp"
#include "utils/debug.hpp"

class BaseScene;
class GameClient;

#define NETWORK_CLASS(Name,Inherited)           \
public:                                         \
    static std::string static_network_class(){  \
        return std::string(#Name);              \
    }                                           \
    virtual std::string network_class()override{\
        return std::string(#Name);              \
    }                                           \
    Name(const GUID& guid): Inherited(guid) {}  \
private:


class NetworkObject: public GameObject{
private:
    bool originator;
    GUID m_guid;
    friend class GameClient;
private:
    friend class BaseScene;
    void _on_introduce()override;
    void _on_destroy()override;
public:
    NetworkObject();
    explicit NetworkObject(const GUID &guid);
    virtual ~NetworkObject() = default;

    NetworkObject *set_guid(const GUID &);


    static std::string static_network_class();               
    virtual std::string network_class();
    const GUID &guid()const;                                          
};

class NetworkObjectsDB{
private:
    typedef NetworkObject* (*ObjectCreator)(BaseScene*,const GUID &);
    static std::unordered_map<std::string,ObjectCreator> m_objects;

public:
    template <typename T>
    static NetworkObject* _obj_creator(BaseScene *scene, const GUID &guid){
        return (NetworkObject*)scene->object_introduce(new T(guid));
    }
    template <typename T>
    static void register_object(){
        m_objects.emplace(T::static_network_class(),&NetworkObjectsDB::_obj_creator<T>);
    }
    ObjectCreator creator(const std::string &class_name);
};




#endif