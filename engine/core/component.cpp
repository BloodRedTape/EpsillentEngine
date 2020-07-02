#include "engine/core/component.hpp"


void Component::set_owner(GameObject* owner){
    mp_owner = owner;
}