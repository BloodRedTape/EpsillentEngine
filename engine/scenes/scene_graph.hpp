#ifndef SCENE_GRAPH
#define SCENE_GRAPH

#include <SFML/Graphics.hpp>
#include "scene_node.hpp"
#include "engine/core/typedefs.hpp"

class RootNode: public SceneNode{
public:
    RootNode(BaseScene* scene){
        mp_parent=nullptr;
        m_dirty = false;
        mp_scene=scene;
    }
    void on_init()override{};
    void on_start()override{};
    void on_destroy()override{};
    void on_update(const float)override{};
};

class SceneGraph{
private:
    RootNode m_root;
public:
    SceneGraph(BaseScene*);

    void update(const float);
    void render();
    _ALWAYS_INLINE_ void add_to_root(SceneNode* p_node){
        m_root.child_add(p_node);
    }

    

};

#endif