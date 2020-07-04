#ifndef SPRITE_2D
#define SPRITE_2D

#include <list>
#include "config/config.hpp"
#include "SFML/Graphics.hpp"
#include "core/component.hpp"

class Renderer2D;

class ENGINE_API Sprite2D: public Component{
private:
    sf::RectangleShape m_shape;
    std::list<Sprite2D>::iterator m_self;
    friend class Renderer2D;
public:
    Sprite2D(GameObject* owner);

    void set_size(float,float);
    void set_size(const sf::Vector2f&);
    void set_color(const sf::Color&);
    void set_texture(sf::Texture*);

    static Sprite2D* init(GameObject*);
    void finalize()override;
    static std::string static_type(){return "Sprite2D";}
};

#endif