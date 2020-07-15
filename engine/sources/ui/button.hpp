#ifndef BUTTON_H
#define BUTTON_H

#include <functional>
#include "ui/widget.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

using callback = std::function<void(void)>;

class Button: public Widget{
private:
    sf::RectangleShape m_shape;
    callback m_callback;
    bool pressed;
public:
    Button(const sf::Vector2f &size, const sf::Color& color, const callback& func);
    void on_update(float dt);
    void on_render();
};

#endif