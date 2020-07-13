#include "physics/physics_engine.hpp"
#include "scenes/game_object.hpp"

PhysicsEngine::PhysicsEngine(){

}

void PhysicsEngine::update(float dt){
    for(Trigger2D& i: triggers){
        for(Trigger2D& j: triggers){
            if(&i!=&j){
                if(i.collide(j)){
                    i.m_callback(j);
                }
            }
        }
        for(Collider2D& cl: colliders){
            if(i.collide(cl)){
                Trigger2D tg(cl.m_body->mp_owner);
                tg.m_size=cl.m_size;
                i.m_callback(tg);
            }
        }
    }
    for(Collider2D& i: colliders){
        for(Collider2D& j: colliders){
            if(&i!=&j)
                i.collide(j);
        }
    }
    for(Rigidbody2D& rb: rigidbodies){
        //rb.force_add(float(-dt)*rb.m_force/((float)rb.m_props.inertia/100.f));
        if(rb.m_props.mass){
            rb.force_add(rb.m_props.gravity);
            rb.mp_owner->translate(rb.m_force*rb.m_props.mass*dt);
            rb.force_add(rb.m_force*-(1.f-(0.9f+rb.m_props.inertia/10.f)));
        }
    }
}

Trigger2D *PhysicsEngine::trigger_2d_new(GameObject* owner){
    auto itr = triggers.insert(triggers.end(),Trigger2D(owner));
    itr->m_self = itr;
    return &*itr;
}

void PhysicsEngine::trigger_2d_delete(Trigger2D* trigger){
    triggers.erase(trigger->m_self);
}

Collider2D *PhysicsEngine::collider_2d_new(Rigidbody2D* owner){
    auto itr = colliders.insert(colliders.end(),Collider2D());
    itr->m_self = itr;
    itr->m_body = owner;
    return &*itr;
}

void PhysicsEngine::collider_2d_delete(Collider2D* collider){
    colliders.erase(collider->m_self);
}

Rigidbody2D *PhysicsEngine::rigidbody_2d_new(GameObject* owner){
    auto itr = rigidbodies.insert(rigidbodies.end(),Rigidbody2D(owner));
    itr->m_self = itr;
    return &*itr;
}

void PhysicsEngine::rigidbody_2d_delete(Rigidbody2D* rb){
    rigidbodies.erase(rb->m_self);
}