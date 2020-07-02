#ifndef SCENE_NODE
#define SCENE_NODE

#include <map>
#include <list> // basicaly have to be replaced with better data structure
#include <queue>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "engine/core/typedefs.hpp"
#include "engine/components/transform.hpp"
#include "engine/utils/debug.hpp"


class BaseScene;
class SceneGraph;
class RootNode;

class GameObject{
private:
    Transform m_transform;
    std::list<GameObject*> m_child_nodes;
    std::list<GameObject*>::iterator m_self;
    BaseScene *mp_scene;
    GameObject *mp_parent;
    bool garbage;
    std::map<std::string,Component*> m_components;

    
private:        
    friend class RootNode;
    friend class BaseScene;
    friend class SceneGraph;
    friend class Transform;
    //add children in update queue
    // apply parent transfrom to self
    void update_traverse(const float dt);
    void render_traverse(std::queue<GameObject*>& r_queue);
    // detach node from parent
    // it will NOT be deleted until you mark_garbage() it
    void detach();
    // detach children node
    void child_detach(GameObject*);
protected:
    virtual void update();
    virtual void render();
public:
    GameObject();
    virtual ~GameObject();


    template <typename T>
    T* component_get(const std::string& name){
        std::map<std::string,Component*>::iterator itr = m_components.find(T::static_type()+name);
        if(itr == m_components.end()){
            Error("Component " + name + " not found");
            return nullptr;
        }
        return static_cast<T*>(itr->second);
    }


    void child_add(GameObject*);
    void children_destroy();

    void destroy();

    //called every loop cycle
    virtual void on_update(const float delta_time){};
    // called on object initialization
    virtual void on_init(){};
    // called after scene context switch
    virtual void on_start(){};
    // called before destroying;
    virtual void on_destroy(){};

    void translate(const sf::Vector2f& r_offset);
    void translate(const float x_offset,const float y_offset);
    void set_rotation(const float angle);
    //void set_origin();

    const sf::Transform& global_transform();
    const sf::Transform& local_transform();
    


};

#endif