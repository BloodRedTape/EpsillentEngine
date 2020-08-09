#include "ui/text_view.hpp"
#include "render/draw_call.hpp"
TextView::TextView(const sf::String &text, const sf::Font &font, const sf::Color &color, uint32 font_size):
    m_text(text,font,font_size)
{
    m_text.setFillColor(color);
}


void TextView::on_render(){
    DrawCallInterface::draw(m_text);
}


void TextView::set_text(const sf::String &text){
    m_text.setString(text);
}
void TextView::set_color(const sf::Color &color){
    m_text.setFillColor(color);
}
void TextView::set_font(const sf::Font &font){
    m_text.setFont(font);
}