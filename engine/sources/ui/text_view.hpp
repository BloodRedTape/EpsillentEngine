#ifndef TEXT_VIEW_H
#define TEXT_VIEW_H

#include "ui/view.hpp"
#include "core/typedefs.hpp"
#include "SFML/System/String.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "core/typedefs.hpp"

class TextView: public View{
protected:
    sf::Text m_text;
public:
    TextView();
    TextView(const sf::String &string,const sf::Font &font,const sf::Color &color = sf::Color::White,uint32 font_size = 30u);

    void on_render()override;

    TextView &set_text(const sf::String &string,const sf::Font &font,const sf::Color &color = sf::Color::White,uint32 font_size = 30u);
    TextView &set_string(const sf::String &string);
    TextView &set_font(const sf::Font &font, uint32 font_size = 30u);
    TextView &set_color(const sf::Color &color);
    TextView &set_position(const sf::Vector2f &position);
    _ALWAYS_INLINE_ const sf::Vector2f &position()const{return m_text.getPosition();}

    sf::Vector2f size();
};

#endif