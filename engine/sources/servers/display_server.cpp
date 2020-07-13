#include "servers/display_server.hpp"
#include "utils/debug.hpp"

DisplayServer * DisplayServer::smp_singleton = nullptr;

DisplayServer::DisplayServer(std::mutex& mtx):
    mutex(mtx),
    mp_display_target(nullptr)
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




void DisplayServer::init_window(sf::VideoMode mode, const char* p_title, uint32 style){
    std::lock_guard<std::mutex> lock(smp_singleton->mutex);
    if(smp_singleton->mp_display_target==nullptr){
        Info("DisplayServer: created new window");
        smp_singleton->mp_display_target = new RenderWindow(mode,p_title,style);
    }else{
        Warning("DisplayServer: trying to init window twice");
    }
} 


sf::Vector2i DisplayServer::window_size(){
    ASSERT_ERROR(smp_singleton,"DisplayServer: wasn not inited");
    return sf::Vector2i(smp_singleton->mp_display_target->getSize().x,smp_singleton->mp_display_target->getSize().y);
}
void DisplayServer::set_frame_rate_limit(int fps){
    if(smp_singleton->mp_display_target!=nullptr)
        mp_display_target->setFramerateLimit(fps);
    else
        Warning("DisplayServer: set_frame_rate_limit: no window inited");
}

void DisplayServer::clear_display(){
    smp_singleton->mp_display_target->clear();
}

void DisplayServer::swap_buffers(){
    smp_singleton->mp_display_target->display();
}
