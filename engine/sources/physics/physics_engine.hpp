#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include "config/config.hpp"
#include <SFML/Graphics.hpp>
#include "components/trigger_2d.hpp"
#include "components/rigidbody_2d.hpp"
#include "physics/collider_2d.hpp"

class ENGINE_API PhysicsEngine{
private:
    std::list<Trigger2D> triggers;
    std::list<Collider2D> colliders;
    std::list<Rigidbody2D> rigidbodies;
    float timer;
public:

    PhysicsEngine();
    
    void update(float dt);
    
    Trigger2D* trigger_2d_new(GameObject*);
    void trigger_2d_delete(Trigger2D*);

    Collider2D* collider_2d_new(Rigidbody2D*);
    void collider_2d_delete(Collider2D*);

    Rigidbody2D* rigidbody_2d_new(GameObject*);
    void rigidbody_2d_delete(Rigidbody2D*);

    std::size_t stats();
};


#endif