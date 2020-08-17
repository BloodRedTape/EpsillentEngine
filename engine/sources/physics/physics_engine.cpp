#include "physics/physics_engine.hpp"
#include "scenes/game_object.hpp"

PhysicsEngine::PhysicsEngine():
    timer(0)
{

}

void PhysicsEngine::update(float dt){
    timer+=dt;

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

    float delay = 0.013f;
    if(timer>=delay){
        timer-=delay;
        for(Rigidbody2D& rb: rigidbodies){
            float intertion = (1.f-rb.m_props.inertia);
            rb.mp_owner->translate(rb.m_force);
            rb.mp_owner->translate(rb.m_translation);
            rb.m_translation=sf::Vector2f(0,0);
            rb.force_add(rb.m_force*-intertion);
            rb.force_add_y(rb.m_force.y*intertion);
            rb.force_add_y(rb.m_props.gravity*rb.m_props.mass);
            //rb.force_add_y(rb.m_props.gravity*(1.f+intertion)*rb.m_props.mass);
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


std::size_t PhysicsEngine::stats(){
    return rigidbodies.size() + colliders.size() + triggers.size();
}