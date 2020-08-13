#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <unordered_map>
#include "config/config.hpp"
#include "core/net/server.hpp"
#include "core/guid.hpp"
#include "SFML/System/Vector2.hpp"

struct NetworkObjectTraits{
    std::string class_name;
    sf::Vector2f local_transform;
    NetworkObjectTraits(const std::string &, const sf::Vector2f &);
    // std::unordered_map of variables;
};

struct ClientData{
    int i; // means nothing
};

class GameServer : public Server<ClientData>{
private:
    std::unordered_map<GUID,NetworkObjectTraits> m_objects;
public:
    GameServer(sf::Uint16 port);
    virtual ~GameServer() = default;


private:
    void bind_handlers();
    void on_object_create(const Event &e, ClientTraits &client);
    void on_object_destroy(const Event &e, ClientTraits &client);
    void on_object_var(const Event &e, ClientTraits &client);
    void on_object_translate(const Event &e, ClientTraits &client);

    void on_connect(ClientTraits &)override;
    void on_disconnect(ClientTraits &)override;

};

#endif