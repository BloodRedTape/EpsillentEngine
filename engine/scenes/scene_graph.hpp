#ifndef SCENE_GRAPH
#define SCENE_GRAPH

#include <SFML/Graphics.hpp>
#include "scene_node.hpp"
#include "engine/core/typedefs.hpp"


class SceneGraph{
private:
    class RootNode: public SceneNode{
    public:
        void init()override{};
        void start()override{};
        void destroy()override{};
        void update(const float){};
    };


    RootNode m_root;
    std::queue<SceneNode*> traverse_order;
public:
    void update_scene(const float);
    _ALWAYS_INLINE_ void add_to_root(SceneNode* p_node){
        m_root.add_child(p_node);
    }
    

};

#endif