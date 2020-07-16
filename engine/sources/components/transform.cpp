#include "components/transform.hpp"
#include "scenes/game_object.hpp"


Transform::Transform(GameObject* owner):
    Component(owner),
    m_global_position(),
    m_local_position(),
    rotation(0),
    m_dirty(false)
{
}

void Transform::translate(const sf::Vector2f& r_offset){
    m_dirty = true;
    m_local_position += r_offset;
}
void Transform::translate(const float x, const float y){
    translate(sf::Vector2f(x,y));
}

void Transform::rotate(const float angle){
    m_dirty = true;
    rotation += angle;
}

sf::Vector2f Transform::global_position(){
    if(m_dirty){
        m_global_position=mp_owner->mp_parent->global_position()+m_local_position;
    }
    return m_global_position;
}

sf::Transform Transform::global_transform(){
    return sf::Transform().rotate(rotation).translate(global_position());
}
const sf::Transform& Transform::local_transform(){
    return sf::Transform().rotate(rotation).translate(m_local_position);
}