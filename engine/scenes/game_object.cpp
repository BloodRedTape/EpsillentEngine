#include "engine/scenes/scene.hpp"
#include "engine/scenes/game_object.hpp"
#include "engine/scenes/scene_manager.hpp"
#include "engine/utils/debug.hpp"

GameObject::GameObject():
    m_transform(this),
    mp_scene(nullptr),
    mp_parent(nullptr),
    garbage(false),
    inited(false)
{
    m_components.insert(std::pair<std::string,Component*>(Transform::static_type()+"Transform",&m_transform));
}

GameObject::~GameObject()
{

}

void GameObject::update_traverse(const float dt){
    for(GameObject* node: m_child_nodes){
        node->update();
        node->on_update(dt);
        /*if(node->m_dirty || dirty){
            node->m_global_transform = m_global_transform*node->m_transform;
            node->m_dirty = false;
            node->update_traverse(dt, true);
        }else{
            node->update_traverse(dt,false);
        }*/
        node->update_traverse(dt);

        
    }
}

void GameObject::render_traverse(std::queue<GameObject*>& traverse_queue){
    for(std::list<GameObject*>::iterator itr = m_child_nodes.begin(); itr!=m_child_nodes.end();itr++){
        traverse_queue.push(*itr);
    }
}
#include <cstdlib>
void GameObject::child_add(GameObject* p_node){
    m_child_nodes.push_back(p_node);
    p_node->mp_parent=this;
    p_node->mp_scene=mp_scene;
    p_node->m_transform.m_dirty=true;
    p_node->m_self = std::prev(m_child_nodes.end());
    if(!p_node->inited){
        p_node->on_init();
        p_node->inited=true;
    }
}
void GameObject::children_destroy(){
    for(GameObject* node: m_child_nodes){
        node->destroy();
    }
}



void GameObject::update(){

}

void GameObject::render(){

}

void GameObject::destroy(){
    if(!garbage){
        on_destroy();
        mp_scene->mark_garbage(this);
        garbage=true;
        for(GameObject* child: m_child_nodes){
            child->destroy();
        }
    }
}

void GameObject::detach(){
    mp_parent->child_detach(this);
    mp_parent=nullptr;
}

void GameObject::child_detach(GameObject* p_node){
    m_child_nodes.erase(p_node->m_self);
}



void GameObject::translate(const sf::Vector2f& r_offset){
    m_transform.translate(r_offset);
}
void GameObject::translate(const float x, const float y){
    translate(sf::Vector2f(x,y));
}

void GameObject::set_rotation(const float angle){
    m_transform.set_rotation(angle);
}


const sf::Transform& GameObject::global_transform(){
    return m_transform.global_transform();
}
const sf::Transform& GameObject::local_transform(){
    return m_transform.local_transform();
}