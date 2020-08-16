#include "components/rigidbody_2d.hpp"
#include "scenes/game_object.hpp"
#include "scenes/scene_manager.hpp"
#include "physics/collider_2d.hpp"

#include "config/config.hpp"

Rigidbody2DProperties::Rigidbody2DProperties():
    mass(1),
    gravity(0,9.8f),
    inertia(0.9),
    rebound(1)
{}


Rigidbody2D::Rigidbody2D(GameObject* owner, const Rigidbody2DProperties& props):
    Component(owner),
    m_props(props),
    m_force(0,0)
{

}


Rigidbody2D& Rigidbody2D::set_properties(const Rigidbody2DProperties& props){
    m_props = props;
    return *this;
}

void Rigidbody2D::force_add(const sf::Vector2f& force){
    m_force += force;
}

void Rigidbody2D::bounce(){
    m_force += m_force*-2.f;
}

void Rigidbody2D::collider_add(const sf::Vector2f& size, const sf::Vector2f& position){
#ifdef DEBUG_MODE
    Info("Collider " + ARG_VEC("size",size));
    auto &shape = mp_owner->component_add<Sprite2D>()->set_size(size.x-6,size.y-6).shape();
    shape.setPosition(position.x+3,position.y+3);
    shape.setFillColor(sf::Color(0,0,0,0));
    shape.setOutlineThickness(3);
    shape.setOutlineColor(sf::Color::Magenta);
#endif
    m_colliders.push_back(mp_owner->scene()->cluster().physics.collider_2d_new(this));
    m_colliders.back()->m_size=sf::FloatRect(position,size);
}

Rigidbody2D *Rigidbody2D::init(GameObject *owner, const Rigidbody2DProperties& props){
    return &owner->scene()->cluster().physics.rigidbody_2d_new(owner)->set_properties(props);
}

void Rigidbody2D::finalize(){
    for(Collider2D* col: m_colliders){
        mp_owner->scene()->cluster().physics.collider_2d_delete(col);
    }
    mp_owner->scene()->cluster().physics.rigidbody_2d_delete(this);
}