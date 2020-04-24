#include "engine/servers/display_server.hpp"
#include "engine/utils/debug.hpp"
DisplayServer * DisplayServer::smp_singleton = nullptr;

DisplayServer::DisplayServer()
{
    if(smp_singleton==nullptr){
        smp_singleton=this;
        Info("DisplayServer: created");
    }else{
        Warning("DisplayServer: messy object inited");
    }
}

DisplayServer::~DisplayServer(){
    Info("DisplayServer: deleted");
}

RenderWindow& DisplayServer::get_display_target(){
    if(mp_display_target!=nullptr){
        return *(get_singleton()->mp_display_target);
    }else{
        Warning("DisplayServer: can't find window...");
        Warning("DisplayServer: created a window using default window configuration");
        return *(get_singleton()->mp_display_target = &init_window());
    }
}

RenderWindow& DisplayServer::init_window(){
    Info("DisplayServer: inited window");
    return *(mp_display_target = new RenderWindow(sf::VideoMode(1280,720),"Engine"));
}   


RenderWindow& DisplayServer::new_window(sf::VideoMode mode, const char* p_title){
    Info("DisplayServer: inited window");
    return *(mp_display_target = new RenderWindow(mode,p_title));
}  

