#include "engine/scenes/scene.hpp"
#include "engine/core/mainframe.hpp"
BaseScene::BaseScene():
    scene_graph(this)
{

}

BaseScene::~BaseScene(){
    
}

void BaseScene::update(const float dt){
    scene_graph.update(dt);
}
void BaseScene::render(){
    scene_renderer.render();
}


void BaseScene::object_introduce(GameObject* node){
    scene_graph.add_to_root(node);
}


void BaseScene::mark_garbage(GameObject* p_candidate){
    garbage.push_front(p_candidate);
}

void BaseScene::clear_garbage(){
    if(!garbage.empty()){
        for(GameObject* candidate: garbage){
            candidate->detach();
            for(auto &component: candidate->m_components){
                component.second->finalize();
            }
        }
        while(!garbage.empty()){
            delete garbage.back();
            garbage.pop_back();
        }
    }
}


