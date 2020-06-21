#include "engine/scenes/scene.hpp"
#include "engine/scenes/scene_node.hpp"
#include "engine/scenes/scene_manager.hpp"
#include "engine/utils/debug.hpp"

SceneNode::SceneNode():
    m_transform(),
    mp_scene(nullptr),
    mp_parent(nullptr),
    garbage(false),
    m_dirty(true)
{

}

SceneNode::~SceneNode()
{

}

void SceneNode::update_traverse(const float dt){
    for(SceneNode* node: m_child_nodes){
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

void SceneNode::render_traverse(std::queue<SceneNode*>& traverse_queue){
    for(std::list<SceneNode*>::iterator itr = m_child_nodes.begin(); itr!=m_child_nodes.end();itr++){
        traverse_queue.push(*itr);
    }
}

void SceneNode::add_child(SceneNode* p_node){
    m_child_nodes.push_back(p_node);
    p_node->set_parent(this,(--m_child_nodes.end()));
    p_node->m_global_transform = m_global_transform*p_node->m_transform;
}
void SceneNode::destroy_children(){
    for(SceneNode* node: m_child_nodes){
        node->destroy();
    }
}

void SceneNode::set_parent(SceneNode *p_parent, std::list<SceneNode*>::iterator itr_in_parent){
    mp_parent=p_parent;
    mp_scene=p_parent->mp_scene;
    m_self=itr_in_parent;
    m_dirty = true;
}

void SceneNode::mark_garbage(){
    mp_scene->mark_garbage(this);
    garbage=true;
}

void SceneNode::update(){

}

void SceneNode::render(){

}

void SceneNode::destroy(){
    if(!garbage){
        on_destroy();
        mark_garbage();
        for(SceneNode* child: m_child_nodes){
            child->destroy();
        }
    }
}

void SceneNode::detach(){
    mp_parent->detach_node(m_self);
    mp_parent=nullptr;
}

void SceneNode::detach_node(std::list<SceneNode*>::iterator node){
    m_child_nodes.erase(node);
}



void SceneNode::translate(const sf::Vector2f& r_offset){
    m_dirty = true;
    m_transform.translate(r_offset);
}
void SceneNode::translate(const float x, const float y){
    translate(sf::Vector2f(x,y));
}

void SceneNode::set_rotation(const float angle){
    m_dirty = true;
    m_transform.rotate(angle);
}


const sf::Transform& SceneNode::global_transform(){
    if(m_dirty){
        m_global_transform=mp_parent->global_transform()*m_transform;
    }
    return m_global_transform;
}