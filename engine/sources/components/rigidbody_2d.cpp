#include "components/rigidbody_2d.hpp"
#include "scenes/game_object.hpp"
#include "scenes/scene_manager.hpp"
#include "physics/collider_2d.hpp"

Rigidbody2DProperties::Rigidbody2DProperties():
    mass(1),
    gravity(0,-9.8f),
    inertia(1)
{}


Rigidbody2D::Rigidbody2D(GameObject* owner):
    Component(owner),
    m_props(),
    m_force(0,0)
{

}


void Rigidbody2D::set_properties(const Rigidbody2DProperties& props){
    m_props = props;
}

void Rigidbody2D::force_add(const sf::Vector2f& force){
    m_force += force;
}

void Rigidbody2D::bounce(){
    m_force += m_force*-2.f;
}

void Rigidbody2D::collider_add(const sf::Vector2f& size, const sf::Vector2f& position){
    m_colliders.push_back(mp_owner->scene()->cluster().physics.collider_2d_new(this));
    m_colliders.back()->m_size=sf::FloatRect(position,size);
}

Rigidbody2D *Rigidbody2D::init(GameObject *owner){
    return owner->scene()->cluster().physics.rigidbody_2d_new(owner);
}

void Rigidbody2D::finalize(){
    for(Collider2D* col: m_colliders){
        mp_owner->scene()->cluster().physics.collider_2d_delete(col);
    }
    mp_owner->scene()->cluster().physics.rigidbody_2d_delete(this);
}