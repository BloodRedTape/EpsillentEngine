#ifndef SCENE_H
#define SCENE_H

#include "config/config.hpp"
#include "core/component.hpp"
#include "scenes/scene_cluster.hpp"
//temp
#include "scenes/scene_graph.hpp"

// to achieve at least something in MY word
// you HAVE TO inherit from THIS class

#include "SFML/System.hpp"

class SceneManager;

class ENGINE_API BaseScene{
protected:
    SceneGraph scene_graph;
    std::list<GameObject*> garbage;
    SceneCluster scene_cluster;
    sf::Clock clock;
    BaseScene();
    virtual ~BaseScene();
private:
    friend class GameObject;
    friend class SceneManager;
    //WARNNING!
    //mark as garbage an ALREADY "destroy()-ed" object
    void mark_garbage(GameObject*);
    bool has_grabage(){return !garbage.empty();}
    void clear_garbage();
public:
    //Engine purpose function
    //Override only if you REALLY understand what is going ond
    virtual void update(const float);
    //Engine purpose function
    //Override only if you REALLY understand what is going on
    virtual void render();
    
    virtual void on_update(const float){};
    virtual void on_init(){};
    // ALL PROCESSORS INITIALIZATIONS SHOULD BE DONE HERE
    virtual void on_start(){};
    virtual void on_destroy(){};


    GameObject* object_introduce(GameObject*);
    GameObject* object_introduce(GameObject*,const sf::Vector2f& pos);

    SceneCluster& cluster(){return scene_cluster;}

    void clear(){scene_graph.clear();}

};

#endif