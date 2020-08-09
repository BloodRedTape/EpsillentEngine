#ifndef TEXT_VIEW_H
#define TEXT_VIEW_H

#include "ui/view.hpp"
#include "core/typedefs.hpp"
#include "SFML/System/String.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

class TextView: public View{
private:
    sf::Text m_text;
public:
    TextView(const sf::String &text, const sf::Font &font, const sf::Color &color = sf::Color::White, uint32 font_size = 30);

    void on_render()override;

    void set_text(const sf::String &text);
    void set_color(const sf::Color &color);
    void set_font(const sf::Font &font);
};

#endif