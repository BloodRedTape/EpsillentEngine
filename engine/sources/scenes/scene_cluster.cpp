#include "scenes/scene_cluster.hpp"


void SceneCluster::update(float dt){
    physics.update(dt);
    for(std::unique_ptr<Component> &comp: components){
        comp->update(dt);
    }
}

void SceneCluster::render(){
    renderer2d.render();
}

std::size_t SceneCluster::stats(){
    return components.size();
}