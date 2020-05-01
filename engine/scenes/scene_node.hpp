#ifndef SCENE_NODE
#define SCENE_NODE

#include <SFML/Graphics.hpp>
#include <list> // basicaly have to be replaced with better data structure
#include <queue>
#include <memory>
#include "engine/core/typedefs.hpp"

class BaseScene;
class RootNode;

class SceneNode{
private:
    std::list<SceneNode*> m_child_nodes;
    std::list<SceneNode*>::iterator m_self;
    BaseScene *mp_scene;
    SceneNode *mp_parent;
    bool garbage;
protected:
    sf::Transform m_transform;
    sf::Transform m_parent_transform;
public:
    SceneNode();
    ~SceneNode();


    //add children in update queue
    // apply parent transfrom to self
    void update_traverse(const float dt);
    void render_traverse(std::queue<SceneNode*>& r_queue);
    
    void add_child(SceneNode*);
    void set_parent(SceneNode*, std::list<SceneNode*>::iterator);

    _ALWAYS_INLINE_ bool is_garbage(){return garbage;}
    void mark_garbage();
    

    //Engine purpose function
    //Override only if you REALLY understand what is going on
    virtual void update();
    //Engine purpose function
    //Override only if you REALLY understand what is going on
    virtual void destroy();

    virtual void render();

    // detach node from parent
    // it will NOT be deleted until you mark_garbage() it
    void detach();
    // detach children node
    void detach_node(std::list<SceneNode*>::iterator);
    //called every loop cycle
    virtual void on_update(const float delta_time)=0;
    // called on object initialization
    virtual void on_init()=0;
    // called after scene context switch
    virtual void on_start()=0;
    // called before destroying;
    virtual void on_destroy()=0;

    void translate(const sf::Vector2f& r_offset);
    void translate(const float x_offset,const float y_offset);
    void set_rotation(const float angle);
    //void set_origin();

    friend class RootNode;
    friend class BaseScene;
};

#endif