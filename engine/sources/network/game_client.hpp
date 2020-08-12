#ifndef GAME_CLIENT_H
#define GAME_CLIENT_H

#include <unordered_map>
#include "config/config.hpp"
#include "core/layer.hpp"
#include "core/net/client.hpp"
#include "core/guid.hpp"
#include "network/network_object.hpp"

class GameClient: public Client{
private:
    std::unordered_map<GUID,NetworkObject*> objects;
public:
    GameClient();
    virtual ~GameClient();
    //override to control whole proccess
    virtual void on_update();
    //override to handle events on your own
    virtual void on_event(const Event &e);

    void obj_create(NetworkObject *);
    void obj_destory(NetworkObject *);

    void on_obj_create(const std::string &class_name, const GUID &guid);
    void on_obj_destory(const GUID &guid);

};

#endif