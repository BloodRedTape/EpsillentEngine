#include "scenes/scene.hpp"
#include "scenes/game_object.hpp"
#include "scenes/scene_manager.hpp"
#include "utils/debug.hpp"

GameObject::GameObject():
    m_transform(this),
    mp_scene(SceneManager::get_current_scene()),
    mp_parent(nullptr),
    m_garbage(false),
    m_introduced(false),
    m_tag("unknown")
{
    m_components.push_back(&m_transform);
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

void GameObject::set_tag(const std::string& tag){
    m_tag = tag;
}

GameObject* GameObject::child_add(GameObject* p_node){
    m_child_nodes.push_back(p_node);
    p_node->mp_parent=this;
    p_node->mp_scene=mp_scene;
    p_node->m_transform.m_dirty=true;
    p_node->m_self = std::prev(m_child_nodes.end());
    if(p_node->m_introduced==false){
        p_node->_on_introduce();
        p_node->on_introduce();
        p_node->m_introduced=true;
    }
    return p_node;
}
void GameObject::children_destroy(){
    for(GameObject* node: m_child_nodes){
        node->destroy();
    }
}

void GameObject::object_introduce(GameObject* object,const sf::Vector2f& relative_pos){
    object->translate(m_transform.m_global_position+relative_pos);
    mp_scene->object_introduce(object);
}



void GameObject::update(){

}

void GameObject::render(){

}

void GameObject::destroy(){
    if(!m_garbage){
        on_destroy();
        _on_destroy();
        mp_scene->mark_garbage(this);
        m_garbage=true;
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

/*
void GameObject::set_transform(const sf::Transform& trans){
    //m_transform.m_transform=trans;
    m_transform.m_dirty=true;
} */

void GameObject::rotate(const float angle){
    m_transform.rotate(angle);
}

sf::Vector2f GameObject::global_position(){
    return m_transform.global_position();
}
const sf::Vector2f& GameObject::local_position(){
    return m_transform.local_position();
}

void GameObject::set_local_position(const sf::Vector2f &position){
    m_transform.set_local_position(position);
}

sf::Transform GameObject::global_transform(){
    return m_transform.global_transform();
}
const sf::Transform& GameObject::local_transform(){
    return m_transform.local_transform();
}