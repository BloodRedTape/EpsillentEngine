#include "components/trigger_2d.hpp"
#include "scenes/game_object.hpp"
#include "SFML/Graphics/Transform.hpp"
#include "scenes/scene_manager.hpp"
#include "config/config.hpp"

void empty_callback(Trigger2D trigger){
    Warning("Trigger2D: callback function was not provided for GameObject with tag: "+ trigger.owner()->tag());
}

Trigger2DProperties::Trigger2DProperties():
    callback(&empty_callback)
{}


Trigger2D::Trigger2D(GameObject *owner, const Trigger2DProperties& props):
    Component(owner)
{
    set_properties(props);
}


bool Trigger2D::collide(const Trigger2D& other){
    return mp_owner->global_transform().transformRect(m_size).intersects(other.mp_owner->global_transform().transformRect(other.m_size));
}

bool Trigger2D::collide(const Collider2D& other){
    return mp_owner->global_transform().transformRect(m_size).intersects(other.body()->owner()->global_transform().transformRect(other.size()));
}

Trigger2D* Trigger2D::init(GameObject *owner,const Trigger2DProperties& props){
    return &owner->scene()->cluster().physics.trigger_2d_new(owner)->set_properties(props);
}

void Trigger2D::finalize(){
    mp_owner->scene()->cluster().physics.trigger_2d_delete(this);
}

Trigger2D& Trigger2D::set_properties(const Trigger2DProperties &props){
    m_callback = props.callback;
    m_size = props.size;
    return *this;
}


