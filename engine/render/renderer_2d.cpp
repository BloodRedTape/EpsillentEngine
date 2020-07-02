#include "engine/utils/debug.hpp"
#include "engine/render/renderer_2d.hpp"
#include "engine/servers/display_server.hpp"

Renderer2D* Renderer2D::smp_singleton = nullptr;

Renderer2D::Renderer2D()
{
    if(smp_singleton==nullptr){
        smp_singleton=this;
        Info("Renderer2D: created");
    }else{
        Warning("Renderer2D: created messy object");
    }
}
Renderer2D::~Renderer2D(){
    Info("Renderer2D: deleted");
}


void Renderer2D::render(sf::Drawable& drawable, const sf::Transform& transfrom){
    DisplayServer::get_singleton()->mp_display_target->draw(drawable,transfrom);
}
void Renderer2D::render(sf::Drawable& drawable){
    DisplayServer::get_singleton()->mp_display_target->draw(drawable);
}
/*
pastgen implementation
void Renderer2D::render(RenderWindow& r_render_window){
    r_render_window.clear();
    
    for(RenderCluster::iterator itr = get_singleton()->mp_cluster->begin(); itr!=get_singleton()->mp_cluster->end(); itr++){
        r_render_window.draw(**itr);
    }
    
   
    r_render_window.display();
}
*/