#include "components/sprite_2d.hpp"
#include "scenes/scene.hpp"
#include "render/renderer_2d.hpp"

#include "scenes/scene_manager.hpp"
Sprite2D::Sprite2D(GameObject* owner):
    Component(owner)
{

}

Sprite2D &Sprite2D::set_size(float x, float y){
    set_size(sf::Vector2f(x,y));
    return *this;
}
Sprite2D &Sprite2D::set_size(const sf::Vector2f& size){
    m_shape.setSize(size);
    return *this;
}
Sprite2D &Sprite2D::set_position(const sf::Vector2f& pos){
    m_shape.setPosition(pos);
    return *this;
}
Sprite2D &Sprite2D::set_position(float x, float y){
    set_position(sf::Vector2f(x,y));
    return *this;
}
Sprite2D &Sprite2D::set_rotation(float angle){
    m_shape.setRotation(angle);
    return *this;
}
Sprite2D &Sprite2D::rotate(float angle){
    m_shape.rotate(angle);
    return *this;
}
Sprite2D &Sprite2D::set_origin(const sf::Vector2f& o){
    m_shape.setOrigin(o);
    return *this;
}

Sprite2D &Sprite2D::set_color(const sf::Color& color){
    m_shape.setFillColor(color);
    return *this;
}

Sprite2D &Sprite2D::set_texture(sf::Texture* texture){
    m_shape.setTexture(texture);
    return *this;
}


Sprite2D* Sprite2D::init(GameObject* owner){
    return owner->scene()->cluster().renderer2d.sprite_new(owner);
}


void Sprite2D::finalize(){
    mp_owner->scene()->cluster().renderer2d.sprite_delete(this);
}