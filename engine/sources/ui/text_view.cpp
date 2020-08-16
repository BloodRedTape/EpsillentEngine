#include "ui/text_view.hpp"
#include "render/draw_call.hpp"
TextView::TextView():
    m_text()
{

}


void TextView::on_render(){
    DrawCallInterface::draw(m_text);
}


void TextView::set_text(const sf::String &text,const sf::Font &font,const sf::Color &color,uint32 font_size){
    m_text.setString(text);
    m_text.setFont(font);
    m_text.setFillColor(color);
    m_text.setCharacterSize(font_size);
}

void TextView::set_string(const sf::String &string){
    m_text.setString(string);
}
void TextView::set_font(const sf::Font &font, uint32 font_size){
    m_text.setFont(font);
    m_text.setCharacterSize(font_size); 
}

void TextView::set_color(const sf::Color &color){
    m_text.setFillColor(color);
}

void TextView::set_position(const sf::Vector2f &position){
    m_text.setPosition(position);
}

sf::Vector2f TextView::size(){
    return sf::Vector2f(m_text.getLocalBounds().width,m_text.getLocalBounds().height);
}
