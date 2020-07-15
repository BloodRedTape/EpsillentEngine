#include "ui/button.hpp"
#include "render/draw_call.hpp"
#include "platform/input.hpp"

Button::Button(const sf::Vector2f& size, const sf::Color& color, const callback& func):
    m_shape(size),
    m_callback(func)
{
    m_shape.setFillColor(color);
}


void Button::on_render(){
    DrawCallInterface::draw(m_shape); 
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