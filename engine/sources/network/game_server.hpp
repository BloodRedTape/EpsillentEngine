#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <unordered_map>
#include "config/config.hpp"
#include "core/net/server.hpp"
#include "core/guid.hpp"
#include "network/network_object.hpp"


struct ClientData{
    std::unordered_map<GUID,NetworkObject> objects;
};

class GameServer : public Server<ClientData>{
private:

public:
    GameServer(sf::Uint16 port);
    virtual ~GameServer() = default;

    void send_all(const Event &e);
    void func();
    void send_except(const Event &e, const Host &exception);
private:

    void on_object_create(const Event &e, ClientTraits &client);
    void on_object_destroy(const Event &e, ClientTraits &client);
};

#endif