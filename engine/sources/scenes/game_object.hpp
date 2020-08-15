#ifndef SCENE_NODE
#define SCENE_NODE

#include <list> // basicaly have to be replaced with better data structure
#include <queue>
#include <memory>
#include <string>
#include "config/config.hpp"
#include <SFML/Graphics.hpp>
#include "core/typedefs.hpp"
#include "components/transform.hpp"
#include "utils/debug.hpp"


class BaseScene;
class SceneGraph;
class RootNode;

class ENGINE_API GameObject{
private:
    Transform m_transform;
    std::list<GameObject*> m_child_nodes;
    std::list<GameObject*>::iterator m_self;
    BaseScene *mp_scene;
    GameObject *mp_parent;
    bool m_garbage : 1;
    std::list<Component*> m_components;
    std::string m_tag;
private:        
    friend class RootNode;
    friend class SceneGraph;
    //add children in update queue
    // apply parent transfrom to self
    void update_traverse(const float dt);


    // detach children node
    void child_detach(GameObject*);
protected:
    virtual void _on_update(float dt){};
    virtual void _on_introduce(){};
    virtual void _on_destroy(){};
public:
    GameObject();
    virtual ~GameObject();

    template <typename T, typename... Props>
    T* component_add(const Props&...props){
        T*t = T::init(this,props...);
        m_components.push_back(t);
        return t;
    }

    void component_remove(Component *component){
        component->finalize();
        m_components.remove(component);
        delete component;
    }

    void components_remove(){
        for(Component *c: m_components)
        {
            c->finalize();
            delete c;
        }
        m_components.clear();
    }

    _ALWAYS_INLINE_ BaseScene* scene(){return mp_scene;};
    _ALWAYS_INLINE_ GameObject* parent(){return mp_parent;}

    const std::string& tag(){return m_tag;}
    void set_tag(const std::string&);

    GameObject* child_add(GameObject*);
    void children_destroy();

    void object_introduce(GameObject*, const sf::Vector2f& relative_pos = sf::Vector2f(0,0));

    void destroy();
    // detach node from parent
    // it will NOT be deleted until you mark_garbage() it
    void detach();

    //called every loop cycle
    virtual void on_update(const float delta_time){};
    // called on object introduction
    virtual void on_introduce(){};
    // called after scene context switch
    virtual void on_start(){};
    // called before destroying;
    virtual void on_destroy(){};

    void translate(const sf::Vector2f& r_offset);
    void translate(const float x_offset,const float y_offset);
    void rotate(const float angle);
    //void set_origin();

    sf::Vector2f global_position();
    const sf::Vector2f& local_position();

    void set_local_position(const sf::Vector2f &position);

    sf::Transform global_transform();
    const sf::Transform& local_transform();

    _ALWAYS_INLINE_ bool garbage(){return m_garbage;}

};

#endif