#include "network/game_server.hpp"
#include "network/objects_protocol.hpp"

GameServer::GameServer(sf::Uint16 port):
    Server(port)
{
    bind_handlers();
    Info("GameServer: created");
}



void GameServer::bind_handlers(){
    event_handler_add(EventCode(Events::ObjectNew),ServerHandler(&GameServer::on_object_create));
    event_handler_add(EventCode(Events::ObjectDel),ServerHandler(&GameServer::on_object_destroy));
    event_handler_add(EventCode(Events::ObjectVar),ServerHandler(&GameServer::on_object_var));
    event_handler_add(EventCode(Events::ObjectTranslate),ServerHandler(&GameServer::on_object_translate));
    Info("GameServer: handler are bound");
}

void GameServer::on_object_create(const Event &e, ClientTraits &client){
    Info("GameServer: client " + client.host.to_string() + " created object " + std::string(*(GUID*)(&e.data[0])) + " Named " + std::string(&e.data[sizeof(GUID)]));
    send_except(e,client.host);
}
void GameServer::on_object_destroy(const Event &e, ClientTraits &client){
    Info("GameServer: client " + client.host.to_string() + " deleted object " + std::string(*(GUID*)(&e.data[0])));
    send_except(e,client.host);
}

void GameServer::on_object_var(const Event &e, ClientTraits &client){
    Info("GameServer: client changed variable");
    send_except(e,client.host);
}

void GameServer::on_object_translate(const Event &e, ClientTraits &client){
    Info("GameServer: client object translated");
    send_except(e,client.host);
}