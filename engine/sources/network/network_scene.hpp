#ifndef NETWORK_SCENE_H
#define NETWORK_SCENE_H

#include <unordered_map>
#include "core/guid.hpp"
#include "scenes/scene.hpp"
#include "core/net/client.hpp"
#include "network/network_object.hpp"
#include "SFML/Network/Packet.hpp"
class NetworkScene: public BaseScene, public Client{
private:
    std::unordered_map<GUID,NetworkObject*> objects;
public:
    NetworkScene();
    virtual ~NetworkScene();

    virtual void update(const float dt)override;

    void event(const Event &e); // event to an object from the other scenes
    NetworkObject *network_object_introduce(NetworkObject *object);
    void network_object_substract(NetworkObject *object);
private:
    void fetch();
    void handle_event(const sf::Packet &e);

    void on_object_new(const sf::Packet &packet);
    void on_object_delete(const sf::Packet &packet);
    void on_object_originator_event(const sf::Packet& packet);
    void on_object_translate(const sf::Packet& packet);
    friend class NetworkObject;
};

#endif