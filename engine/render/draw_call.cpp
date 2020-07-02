#include "engine/render/draw_call.hpp"
#include "engine/utils/debug.hpp"

DrawCallInterface* DrawCallInterface::smp_singleton = nullptr;

DrawCallInterface::DrawCallInterface(sf::RenderWindow* win):
    window(win),
    draw_calls(0)
{
    if(smp_singleton==nullptr){
        smp_singleton = this;
        Info("DrawCallInterface: inited");
    }else{
        Warning("DrawCallInterface: created messy object");
    }
}

DrawCallInterface::~DrawCallInterface(){
    Info("DrawCallInterface: deleted");
}


void DrawCallInterface::draw(const sf::Drawable& drawable, const sf::Transform& transform){
    ASSERT_ERROR(smp_singleton, "DrawCallInterface: has not been inited");
    smp_singleton->window->draw(drawable,transform);
    smp_singleton->draw_calls++;
}

void DrawCallInterface::draw(const sf::Drawable& drawable){
    ASSERT_ERROR(smp_singleton, "DrawCallInterface: has not been inited");
    smp_singleton->window->draw(drawable);
    smp_singleton->draw_calls++;
}

void DrawCallInterface::swap_buffers(){
    ASSERT_ERROR(smp_singleton, "DrawCallInterface: has not been inited");
    smp_singleton->window->display();
    smp_singleton->draw_calls = 0;
}

void DrawCallInterface::clear(){
    ASSERT_ERROR(smp_singleton, "DrawCallInterface: has not been inited");
    smp_singleton->window->clear();
}