#include "scenes/scene.hpp"
#include "utils/debug.hpp"
BaseScene::BaseScene():
    scene_graph(this)
{

}

BaseScene::~BaseScene(){
    on_destroy();
    clear();
    clear_garbage();
    Info("Scene: deleted scene");
}

void BaseScene::update(const float dt){
    scene_graph.update(dt);
    scene_cluster.update(dt);
}
void BaseScene::render(){
    scene_cluster.render();
}


GameObject* BaseScene::object_introduce(GameObject* node){
    ASSERT_ERROR(node->scene()==this,"OwnershipFault, object " + node->tag() + " was created on a different scene and can't be updated by this");
    scene_graph.add_to_root(node);
    return node;
}
GameObject* BaseScene::object_introduce(GameObject* node,const sf::Vector2f& pos){
    node->translate(pos);
    object_introduce(node);
    return node;
}


void BaseScene::garbage_add(GameObject* p_candidate){
    garbage.push_front(p_candidate);
}

void BaseScene::clear_garbage(){
    if(!garbage.empty()){
        Info("Scene: deleted " + std::to_string(garbage.size()) + " objects");
        for(GameObject* candidate: garbage){
            for(Component *component: candidate->m_components){
                component->finalize();
            }
        }
        while(!garbage.empty()){
            garbage.back()->detach();
            delete garbage.back();
            garbage.pop_back();
        }
    }
}


