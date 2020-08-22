#ifndef NETWORK_OBJECT_H
#define NETWORK_OBJECT_H


#include <unordered_map>
#include "config/config.hpp"
#include "core/guid.hpp"
#include "core/net/protocol.hpp"
#include "scenes/scene.hpp"
#include "utils/debug.hpp"
#include "network/objects_protocol.hpp"

class NetworkScene;
class NetworkObjectsDB;

#define NETWORK_CLASS(Name,Inherited)           \
public:                                         \
    static std::string static_network_class(){  \
        return std::string(#Name);              \
    }                                           \
    virtual std::string network_class()override{\
        return std::string(#Name);              \
    }                                           \
    explicit Name(const GUID& guid): Inherited(guid) {}\
private:


class NetworkObject: public GameObject{
public:
    enum Type : uint8{
        Originator,
        Imitator
    };
private:
    Type m_type;
    GUID m_guid;
    float m_timer;
    sf::Vector2f m_network_offset;
    bool m_network_dirty;
    friend class NetworkScene;
    friend class NetworkObjectsDB;
protected:
    void _on_introduce()override;
    void _on_update(float dt)override;
    void _on_destroy()override;
    virtual void on_network_translate(const EventObjectTranslate &e);
public:
    NetworkObject();
    explicit NetworkObject(const GUID &guid);
    virtual ~NetworkObject() = default;

    void network_translate(const sf::Vector2f &offset);
    void network_translate(float x_offset, float y_offset);
    void network_sync_transform();

    NetworkScene *scene(){return (NetworkScene*)(GameObject::scene());};
    //anything you want to send into network
    void network_event(const Event &);

    //send an event to imitator objects
    void originator_event(const OriginatorEvent &);
    //handle an event from originator object
    virtual void on_originator_event(const OriginatorEvent &);
    //virtual void on_imitator_create(const sf::Vector2f &originator_position);
    Type type();

    static std::string static_network_class();               
    virtual std::string network_class();

    NetworkObject *set_guid(const GUID &);
    const GUID &guid()const;                                          
};

class NetworkObjectsDB{
private:
    typedef NetworkObject* (*ObjectCreator)(BaseScene*,const GUID &);
    static std::unordered_map<std::string,ObjectCreator> m_objects;

public:
    template <typename T>
    static NetworkObject* _obj_creator(BaseScene *scene, const GUID &guid){
        return (NetworkObject*)(scene->object_introduce(new T(guid)));
    }
    template <typename Object>
    static void register_object(){
        m_objects.emplace(Object::static_network_class(),&NetworkObjectsDB::_obj_creator<Object>);
    }
    template <typename Object, typename Representation>
    static void register_object_representation(){
        m_objects.emplace(Object::static_network_class(),&NetworkObjectsDB::_obj_creator<Representation>);
    }
    static ObjectCreator creator(const std::string &class_name);
};




#endif