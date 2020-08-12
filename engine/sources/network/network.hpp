#ifndef NETWORK_H
#define NETWORK_H


#include "core/net/protocol.hpp"
#include "core/net/client.hpp"
#include "network/game_client.hpp"

class Network{
private:
    static GameClient *m_client;
public:

    static void initialize(GameClient *client = new GameClient);
    static void connect(const Host &host);
    static void event(const Event &e);
    static void update();
    static void disconnect();
    static void finalize();

    static GameClient *client();

};

#endif