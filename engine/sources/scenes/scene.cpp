#include "scenes/scene.hpp"
#include "core/mainframe.hpp"
#include "utils/debug.hpp"
BaseScene::BaseScene():
    scene_graph(this)
{

}

BaseScene::~BaseScene(){
    
}

void BaseScene::update(const float dt){
    scene_graph.update(dt);
    scene_cluster.update(dt);
}
void BaseScene::render(){
    scene_cluster.render();
}


void BaseScene::object_introduce(GameObject* node){
    ASSERT_ERROR(node->mp_scene=this,"OwnershipFault, object " + node->m_tag + " was created on a different scene and can't be updated by this");
    scene_graph.add_to_root(node);
}
void BaseScene::object_introduce(GameObject* node,const sf::Vector2f& pos){
    object_introduce(node);
    node->translate(pos);
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


