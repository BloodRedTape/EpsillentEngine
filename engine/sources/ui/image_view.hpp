#ifndef IMAGE_VIEW_H
#define IMAGE_VIEW_H

#include "ui/view.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class ImageView: public View{
private:
    sf::RectangleShape m_shape;
public:
    ImageView(const sf::Vector2f &size = sf::Vector2f(0,0));
    void on_render()override;
    ImageView &set_size(const sf::Vector2f &size);
    ImageView &set_position(const sf::Vector2f &position);
    ImageView &set_texture(sf::Texture *texture);
};

#endif