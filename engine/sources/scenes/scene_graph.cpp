#include "scenes/scene_graph.hpp"
#include "utils/debug.hpp"

SceneGraph::SceneGraph(BaseScene* p_scene):
    m_root(p_scene)
{
}

void SceneGraph::update(const float dt){
    m_root.update_traverse(dt);    
}


void SceneGraph::clear(){
    m_root.children_destroy();
}