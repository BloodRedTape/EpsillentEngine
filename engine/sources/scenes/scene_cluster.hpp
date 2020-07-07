#ifndef SCENE_COMPLEX_H
#define SCENE_COMPLEX_H

#include <list>
#include "core/component.hpp"
#include "render/renderer_2d.hpp"
#include "physics/physics_engine.hpp"


struct SceneCluster{
    Renderer2D renderer2d;
    PhysicsEngine physics;
    std::list<Component*> components;

    void render();
    void update(float dt);  
};
#endif