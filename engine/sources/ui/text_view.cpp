#include "ui/text_view.hpp"
#include "render/draw_call.hpp"
TextView::TextView():
    m_text()
{

}
TextView::TextView(const sf::String &string,const sf::Font &font,const sf::Color &color = sf::Color::White,uint32 font_size = 30u){
    set_text(string,font,color,font_size);
}


void TextView::on_render(){
    DrawCallInterface::draw(m_text);
}


TextView &TextView::set_text(const sf::String &text,const sf::Font &font,const sf::Color &color,uint32 font_size){
    m_text.setString(text);
    m_text.setFont(font);
    m_text.setFillColor(color);
    m_text.setCharacterSize(font_size);
    return *this;
}

TextView &TextView::set_string(const sf::String &string){
    m_text.setString(string);
    return *this;
}
TextView &TextView::set_font(const sf::Font &font, uint32 font_size){
    m_text.setFont(font);
    m_text.setCharacterSize(font_size); 
    return *this;
}

TextView &TextView::set_color(const sf::Color &color){
    m_text.setFillColor(color);
    return *this;
}

TextView &TextView::set_position(const sf::Vector2f &position){
    m_text.setPosition(position);
    return *this;
}

sf::Vector2f TextView::size(){
    return sf::Vector2f(m_text.getLocalBounds().width,m_text.getLocalBounds().height);
}
