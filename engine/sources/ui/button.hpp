#ifndef BUTTON_H
#define BUTTON_H

#include <functional>
#include "ui/view.hpp"
#include "ui/text_view.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "core/typedefs.hpp"

using callback = std::function<void(void)>;


class Button: public View{
private:
    TextView m_text;
    sf::RectangleShape m_shape;
    callback m_callback;
    bool pressed;
    void center_text();
public:
    Button(const sf::Vector2f &size = sf::Vector2f(0,0), const sf::Color& color = sf::Color::White);
    void on_update(float dt)override;
    void on_render()override;
    Button& set_position(const sf::Vector2f &position);
    _ALWAYS_INLINE_ const sf::Vector2f &position()const{return m_shape.getPosition();}
    Button& set_texture(sf::Texture *texture);
    Button& set_callback(const callback& func);
    Button& set_text(const sf::String &string,const sf::Font &font,const sf::Color &color = sf::Color::White,uint32 font_size = 30u);

};

#endif