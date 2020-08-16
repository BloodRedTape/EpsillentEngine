#ifndef TEXT_VIEW_H
#define TEXT_VIEW_H

#include "ui/view.hpp"
#include "core/typedefs.hpp"
#include "SFML/System/String.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

class TextView: public View{
protected:
    sf::Text m_text;
public:
    TextView();

    void on_render()override;

    void set_text(const sf::String &string,const sf::Font &font,const sf::Color &color = sf::Color::White,uint32 font_size = 30u);
    void set_string(const sf::String &string);
    void set_font(const sf::Font &font, uint32 font_size = 30u);
    void set_color(const sf::Color &color);
    void set_position(const sf::Vector2f &position);

    sf::Vector2f size();
};

#endif