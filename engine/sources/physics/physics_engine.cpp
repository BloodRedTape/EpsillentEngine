#include "physics/physics_engine.hpp"


PhysicsEngine::PhysicsEngine(){

}

void PhysicsEngine::update(){
    for(Collider2D& i: colliders){
        for(Collider2D& j: colliders){
            if(&i!=&j){
                if(i.collide(j)){
                    i.m_callback(j);
                }
            }
        }
    }
}

Collider2D *PhysicsEngine::collider_2d_new(GameObject* owner){
    auto itr = colliders.insert(colliders.end(),Collider2D(owner));
    itr->m_self = itr;
    return &*itr;
}

void PhysicsEngine::collider_2d_delete(Collider2D* collider){
    colliders.erase(collider->m_self);
}