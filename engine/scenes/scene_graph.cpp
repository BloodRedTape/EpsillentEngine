#include "engine/scenes/scene_graph.hpp"


void SceneGraph::update_scene(const float dt){
    traverse_order.push(&m_root);
    while (!traverse_order.empty())
    {
        traverse_order.front()->traverse(traverse_order);
        traverse_order.front()->engine_update();
        traverse_order.front()->update(dt);
        traverse_order.pop();
    }
    
}