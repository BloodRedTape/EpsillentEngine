#include "core/component.hpp"


Component::Component(GameObject* owner):
mp_owner(owner)
{
    
}


GameObject * Component::owner()const{
    return mp_owner;
}