#include "components/trigger_2d.hpp"
#include "scenes/game_object.hpp"
#include "SFML/Graphics/Transform.hpp"
#include "scenes/scene_manager.hpp"

Trigger2DProperties::Trigger2DProperties():
    callback(&Trigger2D::empty_callback)
{}


Trigger2D::Trigger2D(GameObject *owner):
    Component(owner)
{
    set_properties(Trigger2DProperties());
}


bool Trigger2D::collide(const Trigger2D& other){
    return mp_owner->global_transform().transformRect(m_size).intersects(other.mp_owner->global_transform().transformRect(other.m_size));
}


Trigger2D* Trigger2D::init(GameObject *owner){
    return owner->scene()->cluster().physics.trigger_2d_new(owner);
}

void Trigger2D::finalize(){
    mp_owner->scene()->cluster().physics.trigger_2d_delete(this);
}


void Trigger2D::set_properties(const Trigger2DProperties &props){
    m_callback = props.callback;
    m_size = props.size;
}


