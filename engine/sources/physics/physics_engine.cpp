#include "physics/physics_engine.hpp"


PhysicsEngine::PhysicsEngine(){

}

void PhysicsEngine::update(){
    for(Trigger2D& i: colliders){
        for(Trigger2D& j: colliders){
            if(&i!=&j){
                if(i.collide(j)){
                    i.m_callback(j);
                }
            }
        }
    }
}

Trigger2D *PhysicsEngine::collider_2d_new(GameObject* owner){
    auto itr = colliders.insert(colliders.end(),Trigger2D(owner));
    itr->m_self = itr;
    return &*itr;
}

void PhysicsEngine::collider_2d_delete(Trigger2D* collider){
    colliders.erase(collider->m_self);
}