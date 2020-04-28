#ifndef SPRITE
#define SPRITE

#include "engine/scenes/scene_node.hpp"

class Sprite: public SceneNode{
protected:
    sf::RectangleShape m_shape;
public:
    virtual void init()override;
    virtual void update(float dt)override;
    void engine_update();
    virtual void start()override;
    virtual void destroy()override;

    _ALWAYS_INLINE_ virtual void set_size(const sf::Vector2f& size){
        m_shape.setSize(size);
    };
    _ALWAYS_INLINE_ virtual void set_size(const float& x, const float& y){
        set_size(sf::Vector2f(x,y));
    }

    _ALWAYS_INLINE_ void set_color(const sf::Color& color){
        m_shape.setFillColor(color);
    }
    _ALWAYS_INLINE_ void set_texture(sf::Texture* p_texture){
        m_shape.setTexture(p_texture, true);
    };


    
};

#endif 