#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include "config/config.hpp"
#include <SFML/Graphics.hpp>
#include "components/collider_2d.hpp"

class ENGINE_API PhysicsEngine{
private:
    std::list<Collider2D> colliders;
public:

    PhysicsEngine();
    
    void update();
    
    Collider2D* collider_2d_new(GameObject*);
    void collider_2d_delete(Collider2D*);

};


#endif