#include "components/collider_2d.hpp"
#include "scenes/game_object.hpp"
#include "SFML/Graphics/Transform.hpp"
#include "scenes/scene_manager.hpp"

Collider2DProperties::Collider2DProperties():
    callback(&Collider2D::empty_callback)
{}


Collider2D::Collider2D(GameObject *owner):
    Component(owner)
{
    set_properties(Collider2DProperties());
}


bool Collider2D::collide(const Collider2D& other){
    return mp_owner->global_transform().transformRect(m_size).intersects(other.mp_owner->global_transform().transformRect(other.m_size));
}


Collider2D* Collider2D::init(GameObject *owner){
    return owner->scene()->cluster().physics.collider_2d_new(owner);
}

void Collider2D::finalize(){
    mp_owner->scene()->cluster().physics.collider_2d_delete(this);
}


void Collider2D::set_properties(const Collider2DProperties &props){
    m_callback = props.callback;
    m_size = props.size;
}


