#include "servers/display_server.hpp"
#include "utils/debug.hpp"

std::mutex *DisplayServer::p_sync_mutex = nullptr;
sf::RenderWindow* DisplayServer::mp_display_target = nullptr;

void DisplayServer::initialize(std::mutex *sync_mutex,sf::VideoMode mode, const char* p_title, uint32 style){
    p_sync_mutex = sync_mutex;
    mp_display_target = new RenderWindow(mode,p_title,style); 
    Info("DisplayServer: inited"); 
} 
void DisplayServer::finalize() {
    delete mp_display_target;
    Info("DisplayServer: finalized");
}

sf::Vector2i DisplayServer::window_size(){
    return sf::Vector2i(mp_display_target->getSize().x,mp_display_target->getSize().y);
}
void DisplayServer::set_frame_rate_limit(int fps){        
    mp_display_target->setFramerateLimit(fps);
}

void DisplayServer::clear_display(){
    mp_display_target->clear();
}

void DisplayServer::swap_buffers(){
    mp_display_target->display();
}
