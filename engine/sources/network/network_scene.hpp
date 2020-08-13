#ifndef NETWORK_SCENE_H
#define NETWORK_SCENE_H

#include <unordered_map>
#include "core/guid.hpp"
#include "scenes/scene.hpp"
#include "core/net/client.hpp"
#include "network/network_object.hpp"

class NetworkScene: public BaseScene, public Client{
private:
    std::unordered_map<GUID,NetworkObject*> objects;
public:
    NetworkScene();
    virtual ~NetworkScene();

    virtual void update(const float dt)override;

    void event(const Event &e); // event to an object from the other scenes

private:
    void fetch();
    void handle_event(const Event &e);

    void object_new(NetworkObject *object);
    void object_delete(NetworkObject *object);

    void on_object_new(const GUID &guid,const sf::Vector2f &position, const std::string &class_name);
    void on_object_delete(const GUID &guid);
    void on_object_event(const GUID &guid, const Event &e);
    void on_object_var(const GUID &guid, const Event &e);
    void on_object_translate(const GUID &guid, const Event &e);
    friend class NetworkObject;
};

#endif