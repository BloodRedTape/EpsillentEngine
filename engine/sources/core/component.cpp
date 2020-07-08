#include "core/component.hpp"


Component::Component(GameObject* owner):
mp_owner(owner)
{
    
}


GameObject * Component::owner(){
    return mp_owner;
}