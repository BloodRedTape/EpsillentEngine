#ifndef SPRITE_2D
#define SPRITE_2D

#include <list>
#include "config/config.hpp"
#include "SFML/Graphics.hpp"
#include "core/component.hpp"
#include "core/typedefs.hpp"
class Renderer2D;

class ENGINE_API Sprite2D: public Component{
private:
    sf::RectangleShape m_shape;
    std::list<Sprite2D>::iterator m_self;
    friend class Renderer2D;
public:
    Sprite2D(GameObject* owner);

    Sprite2D &set_size(float,float);
    Sprite2D &set_size(const sf::Vector2f&);
    Sprite2D &set_position(float,float);
    Sprite2D &set_position(const sf::Vector2f&);
    Sprite2D &set_rotation(float);
    Sprite2D &rotate(float);
    Sprite2D &set_origin(const sf::Vector2f&);
    Sprite2D &set_color(const sf::Color&);
    Sprite2D &set_texture(sf::Texture*);

    _ALWAYS_INLINE_ sf::RectangleShape &shape(){return m_shape;}

    float rotation();

    static Sprite2D* init(GameObject*);
    void finalize()override;
    static std::string static_type(){return "Sprite2D";}
};

#endif