#include "scenes/scene.hpp"
#include "utils/debug.hpp"
BaseScene::BaseScene():
    scene_graph(this),
    p_ui_controller(nullptr)
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
void BaseScene::set_ui_controller(UIController *controller){
    p_ui_controller=controller;
}

GameObject* BaseScene::object_introduce(GameObject* node,const sf::Vector2f& parent_offset){
    ASSERT_ERROR(node->scene()==this,"OwnershipFault, object " + node->tag() + " was created on a different scene and can't be updated by this");
    node->translate(parent_offset);
    scene_graph.add_to_root(node);
    return node;
}

void BaseScene::garbage_add(GameObject* p_candidate){
    garbage.push_front(p_candidate);
}

void BaseScene::clear_garbage(){
    while(!garbage.empty()){
        garbage.back()->detach();
        delete garbage.back();
        garbage.pop_back();
    }
}


