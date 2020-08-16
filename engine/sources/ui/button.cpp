#include "ui/button.hpp"
#include "render/draw_call.hpp"
#include "platform/input.hpp"
#include "utils/debug.hpp"
void null_callback(void){
    Warning("Button: callback was not provided");
}

Button::Button(const sf::Vector2f& size, const sf::Color& color):
    m_shape(size),
    m_callback(&null_callback)
{
    m_shape.setFillColor(color);
}


void Button::on_render(){
    DrawCallInterface::draw(m_shape); 
    DrawCallInterface::draw(m_text);
}

void Button::on_update(float dt){
    if(Input::mouse_pressed(MouseButton::Left)){
        if(m_shape.getGlobalBounds().contains(Input::mouse_position().x,Input::mouse_position().y) && !pressed){
            pressed = true;
            m_callback();
        }
    }else{
        pressed = false;
    }
}

void Button::set_callback(const callback& func){
    m_callback = func;
}

