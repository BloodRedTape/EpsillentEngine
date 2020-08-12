#include "network/network.hpp"
#include "engine.hpp"
GameClient *Network::m_client = nullptr;


void Network::initialize(GameClient *client){
    ASSERT_ERROR(m_client==nullptr,"Network: has already been initialized");
    m_client = client;
    Info("Network: initialized");
}

void Network::connect(const Host &host){
    ASSERT_ERROR(m_client!=nullptr,"Network: is not initialized");
    m_client->connect(host);
}

void Network::event(const Event &e){
    ASSERT_ERROR(m_client!=nullptr,"Network: is not initialized");
    m_client->send(e);
}

void Network::update(){
    if(m_client)
        m_client->on_update();
}

void Network::disconnect(){
    ASSERT_ERROR(m_client!=nullptr,"Network: is not initialized");
    m_client->disconnect();
}

void Network::finalize(){
    if(m_client)
        delete m_client;
    m_client = nullptr;
    Info("Network: finalized");
}

GameClient *Network::client(){
    if(m_client)
        return m_client;
    else
        Error("Network: is not initialized");
    return nullptr;
}