#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include "config/config.hpp"
#include <SFML/Graphics.hpp>
#include "components/trigger_2d.hpp"

class ENGINE_API PhysicsEngine{
private:
    std::list<Trigger2D> colliders;
public:

    PhysicsEngine();
    
    void update();
    
    Trigger2D* collider_2d_new(GameObject*);
    void collider_2d_delete(Trigger2D*);

};


#endif