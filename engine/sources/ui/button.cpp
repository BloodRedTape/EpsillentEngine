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

void Button::center_text(){
    const sf::Vector2f &size = m_shape.getSize();
    sf::Vector2f text_size = m_text.size();
    m_text.set_position(m_shape.getPosition()+sf::Vector2f(size.x/2-text_size.x/2,size.y/2-text_size.y/2));
}

void Button::on_render(){
    DrawCallInterface::draw(m_shape); 
    m_text.on_render();
}

void Button::set_position(const sf::Vector2f &position){
    m_shape.setPosition(position);
    center_text();
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

void Button::set_text(const sf::String &text,const sf::Font &font,const sf::Color &color,uint32 font_size){
    m_text.set_text(text,font,color,font_size);
    center_text();
}


