#include "engine/scenes/scene.hpp"
#include "engine/core/mainframe.hpp"
BaseScene::BaseScene(){

}

BaseScene::~BaseScene(){
    
}

void BaseScene::engine_update(const float dt){
    scene_graph.update_scene(dt);
}