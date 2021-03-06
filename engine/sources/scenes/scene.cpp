#include "scenes/scene.hpp"
#include "utils/debug.hpp"
BaseScene::BaseScene():
    scene_graph(this),
    p_ui_controller(nullptr)
{

}

BaseScene::~BaseScene(){
    clear_garbage();
    on_destroy();
    clear();
    clear_garbage();
    Info("Scene: Destroyed");
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

void BaseScene::object_substract(GameObject *object){
    if(!object->m_garbage){
        object->m_garbage = true;
        object->on_destroy();
        garbage_add(object);
        object->children_destroy();
    }else{
        Warning("Scene: trying to destroy " + object->m_tag + " objecet twice \nthis will most probably cause a segmantation fault so fix this shit up right NOW");
    }
}

void BaseScene::garbage_add(GameObject* p_candidate){
    garbage.push_front(p_candidate);
}

void BaseScene::clear_garbage(){
    for(GameObject *o: garbage)
        o->detach();
    while(!garbage.empty()){
        delete garbage.back();
        garbage.pop_back();
    }
}


