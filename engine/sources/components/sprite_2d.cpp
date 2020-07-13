#include "components/sprite_2d.hpp"
#include "scenes/scene.hpp"
#include "render/renderer_2d.hpp"

#include "scenes/scene_manager.hpp"
Sprite2D::Sprite2D(GameObject* owner):
    Component(owner)
{

}

void Sprite2D::set_size(float x, float y){
    set_size(sf::Vector2f(x,y));
}
void Sprite2D::set_size(const sf::Vector2f& size){
    m_shape.setSize(size);
}
void Sprite2D::set_rotation(float angle){
    m_shape.setRotation(angle);
}
void Sprite2D::rotate(float angle){
    m_shape.rotate(angle);
}
void Sprite2D::set_origin(const sf::Vector2f& o){
    m_shape.setOrigin(o);
}

void Sprite2D::set_color(const sf::Color& color){
    m_shape.setFillColor(color);
}

void Sprite2D::set_texture(sf::Texture* texture){
    m_shape.setTexture(texture);
}


Sprite2D* Sprite2D::init(GameObject* owner){
    return owner->scene()->cluster().renderer2d.sprite_new(owner);
}


void Sprite2D::finalize(){
    mp_owner->scene()->cluster().renderer2d.sprite_delete(this);
}