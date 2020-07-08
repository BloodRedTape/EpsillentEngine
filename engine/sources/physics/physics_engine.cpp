#include "physics/physics_engine.hpp"


PhysicsEngine::PhysicsEngine(){

}

void PhysicsEngine::update(){
    for(Trigger2D& i: triggers){
        for(Trigger2D& j: triggers){
            if(&i!=&j){
                if(i.collide(j)){
                    i.m_callback(j);
                }
            }
        }
    }
}

Trigger2D *PhysicsEngine::trigger_2d_new(GameObject* owner){
    auto itr = triggers.insert(triggers.end(),Trigger2D(owner));
    itr->m_self = itr;
    return &*itr;
}

void PhysicsEngine::trigger_2d_delete(Trigger2D* collider){
    triggers.erase(collider->m_self);
}