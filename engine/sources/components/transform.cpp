#include "components/transform.hpp"
#include "scenes/game_object.hpp"


Transform::Transform(GameObject* owner):
    Component(owner),
    m_transform(),
    m_global_transform(),
    m_dirty(false)
{
}

void Transform::translate(const sf::Vector2f& r_offset){
    m_dirty = true;
    m_transform.translate(sf::Vector2f(r_offset.x,r_offset.y*-1));
}
void Transform::translate(const float x, const float y){
    translate(sf::Vector2f(x,y));
}

void Transform::rotate(const float angle){
    m_dirty = true;
    m_transform.rotate(angle);
}

sf::Transform Transform::global_transform(){
    if(m_dirty){
        m_global_transform=mp_owner->mp_parent->global_transform()*m_transform;
    }
    return m_global_transform;
}
const sf::Transform& Transform::local_transform(){
    return m_transform;
}