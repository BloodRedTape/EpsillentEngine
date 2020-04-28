#include "engine/scenes/scene_node.hpp"

void SceneNode::traverse(std::queue<SceneNode*>& traverse_queue){
    for(std::list<SceneNode*>::iterator itr = m_child_nodes.begin(); itr!=m_child_nodes.end();itr++){
        (*itr)->m_parent_transform = m_parent_transform*m_transform;
        traverse_queue.push(*itr);
    }
}

void SceneNode::engine_update(){

}

void SceneNode::add_child(SceneNode* p_node){
    m_child_nodes.push_back(p_node);
}

void SceneNode::translate(const sf::Vector2f& r_offset){
    m_transform.translate(r_offset);
}
void SceneNode::translate(const float x, const float y){
    translate(sf::Vector2f(x,y));
}

void SceneNode::set_rotation(const float angle){
    m_transform.rotate(angle);
}