#ifndef BUTTON_H
#define BUTTON_H

#include <functional>
#include "ui/view.hpp"
#include "ui/text_view.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

using callback = std::function<void(void)>;


class Button: public View{
private:
    TextView m_text;
    sf::RectangleShape m_shape;
    callback m_callback;
    bool pressed;
    void center_text();
public:
    Button(const sf::Vector2f &size, const sf::Color& color);
    void on_update(float dt)override;
    void on_render()override;
    void set_position(const sf::Vector2f &position);
    void set_callback(const callback& func);
    void set_text(const sf::String &string,const sf::Font &font,const sf::Color &color = sf::Color::White,uint32 font_size = 30u);

};

#endif