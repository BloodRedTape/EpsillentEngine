#include "engine/scenes/scene_graph.hpp"
#include "engine/utils/debug.hpp"

SceneGraph::SceneGraph(BaseScene* p_scene):
    m_root(p_scene)
{
}

void SceneGraph::update(const float dt){
    m_root.update_traverse(dt);    
}

void SceneGraph::render(){
    std::queue<SceneNode*> traverse_order;
    traverse_order.push(&m_root);
    while (!traverse_order.empty())
    {
        traverse_order.front()->render_traverse(traverse_order);
        traverse_order.front()->render();
        traverse_order.pop();
    };
}