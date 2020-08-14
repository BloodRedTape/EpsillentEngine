#include "network/game_server.hpp"
#include "network/objects_protocol.hpp"
#include "string.h"

NetworkObjectTraits::NetworkObjectTraits(const std::string &s,const sf::Vector2f &pos):
    class_name(s),
    local_transform(pos)
{}

GameServer::GameServer(sf::Uint16 port):
    Server(port)
{
    bind_handlers();
    Info("GameServer: created");
}



void GameServer::bind_handlers(){
    event_handler_add(EventCode(Events::ObjectNew),ServerHandler(&GameServer::on_object_create));
    event_handler_add(EventCode(Events::ObjectDelete),ServerHandler(&GameServer::on_object_destroy));
    event_handler_add(EventCode(Events::ObjectOriginatorEvent),ServerHandler(&GameServer::on_object_originator));
    event_handler_add(EventCode(Events::ObjectTranslate),ServerHandler(&GameServer::on_object_translate));
    Info("GameServer: handler are bound");
}

void GameServer::on_object_create(const sf::Packet &packet, ClientTraits &client){
    EventObjectNew &event = *(EventObjectNew*)packet.getData();
    Info("GameServer: client " + client.host.to_string() + " created object " + std::string(event.guid) + " Named " + std::string(event.class_name));
    m_objects.emplace(event.guid,NetworkObjectTraits(event.class_name,event.position));
    send_except(packet.getData(),packet.getDataSize(),client.host);
}
void GameServer::on_object_destroy(const sf::Packet &packet, ClientTraits &client){
    EventObjectDelete &event = *(EventObjectDelete*)packet.getData();
    Info("GameServer: client " + client.host.to_string() + " deleted object " + std::string(event.guid));
    m_objects.erase(event.guid);
    send_except(packet.getData(),packet.getDataSize(),client.host);   
}

void GameServer::on_object_var_init(const sf::Packet &packet, ClientTraits &client){
    send_except(packet.getData(),packet.getDataSize(),client.host);
    Info("GameServer: inited variable");
}
void GameServer::on_object_var_changed(const sf::Packet &packet, ClientTraits &client){
    Info("GameServer: variable changed");
    send_except(packet.getData(),packet.getDataSize(),client.host);
}

void GameServer::on_object_translate(const sf::Packet &packet, ClientTraits &client){
    EventObjectTranslate &event = *(EventObjectTranslate*)packet.getData();
    m_objects.find(event.guid)->second.local_transform = event.position;
    send_except(packet.getData(),packet.getDataSize(),client.host);
}
void GameServer::on_object_originator(const sf::Packet &packet, ClientTraits &client){
    EventObjectOriginator &event = *(EventObjectOriginator*)packet.getData();
    Info("GameServer: "+std::string(event.guid)+" originator event");
    send_except(packet.getData(),packet.getDataSize(),client.host);
}

void GameServer::on_connect(ClientTraits &c){
    EventObjectNew e;
    for(auto &object: m_objects){
        e.guid = object.first;
        e.position=object.second.local_transform;
        memcpy(e.class_name,object.second.class_name.c_str(),object.second.class_name.size()+1);
        send(c.host,&e,sizeof(e));
    }
}
void GameServer::on_disconnect(ClientTraits &c){
    
}