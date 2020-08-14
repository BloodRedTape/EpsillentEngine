#ifndef SCENE_GRAPH
#define SCENE_GRAPH

#include "config/config.hpp"
#include <SFML/Graphics.hpp>
#include "game_object.hpp"
#include "core/typedefs.hpp"

class ENGINE_API RootNode: public GameObject{
public:
    RootNode(BaseScene* scene){
        mp_parent=nullptr;
        mp_scene=scene;
    }
};

class ENGINE_API SceneGraph{
private:
    RootNode m_root;
public:
    SceneGraph(BaseScene*);

    void update(const float);
    _ALWAYS_INLINE_ void add_to_root(GameObject* p_node){
        m_root.child_add(p_node);
    }

    void clear();

    

};

#endif