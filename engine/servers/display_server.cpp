#include "engine/servers/display_server.hpp"
#include "engine/utils/debug.hpp"

DisplayServer * DisplayServer::smp_singleton = nullptr;

DisplayServer::DisplayServer(std::mutex& mtx):
    mutex(mtx)
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




void DisplayServer::init_window(sf::VideoMode mode, const char* p_title){
    std::lock_guard<std::mutex> lock(smp_singleton->mutex);
    Info("DisplayServer: created new window");
    if(smp_singleton->mp_display_target==nullptr)
        smp_singleton->mp_display_target = new RenderWindow(mode,p_title);
    else
        Warning("DisplayServer: trying to init window twice");
}  

void DisplayServer::set_frame_rate_limit(int fps){
    if(smp_singleton->mp_display_target!=nullptr)
        mp_display_target->setFramerateLimit(fps);
    else
        Warning("DisplayServer: set_frame_rate_limit: no window inited");
}

void DisplayServer::clear_display(){
    draw_calls=0;
    smp_singleton->mp_display_target->clear();
}

void DisplayServer::swap_buffers(){
    smp_singleton->mp_display_target->display();
}
