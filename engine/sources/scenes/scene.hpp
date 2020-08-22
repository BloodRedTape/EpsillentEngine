#ifndef SCENE_H
#define SCENE_H

#include "config/config.hpp"
#include "core/component.hpp"
#include "scenes/scene_cluster.hpp"
#include "ui/ui_controller.hpp"
#include "scenes/scene_graph.hpp"

// to achieve at least something in MY word
// you HAVE TO inherit from THIS class

#include "SFML/System.hpp"

class SceneManager;
class NetworkScene;

class ENGINE_API BaseScene{
protected:
    SceneGraph scene_graph;
    std::list<GameObject*> garbage;
    SceneCluster scene_cluster;
    UIController *p_ui_controller;
private:
    friend class GameObject;
    friend class SceneManager;
    //because it is still a scene which needs all of the cool handles
    friend class NetworkScene;
    //WARNNING!
    //mark as garbage an ALREADY "destroy()-ed" object
    void garbage_add(GameObject*);
    _ALWAYS_INLINE_ bool has_grabage(){return !garbage.empty();}
    void clear_garbage();
public:
    BaseScene();
    virtual ~BaseScene();
    //Engine purpose function
    //Override only if you REALLY understand what is going ond
    virtual void update(const float);
    //Engine purpose function
    //Override only if you REALLY understand what is going on
    virtual void render();
    
    virtual void on_update(const float){};
    virtual void on_introduce(){};
    // ALL PROCESSORS INITIALIZATIONS SHOULD BE DONE HERE
    virtual void on_start(){};
    virtual void on_destroy(){};

    void set_ui_controller(UIController *controller);
    _ALWAYS_INLINE_ UIController *ui_controller(){return p_ui_controller;};


    GameObject* object_introduce(GameObject*,const sf::Vector2f& parent_offset = sf::Vector2f(0,0));
    void object_substract(GameObject *object);

    _ALWAYS_INLINE_ SceneCluster& cluster(){return scene_cluster;}

    _ALWAYS_INLINE_ void clear(){scene_graph.clear();}

};

#endif