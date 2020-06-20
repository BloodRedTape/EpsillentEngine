#ifndef SCENE_H
#define SCENE_H

#include "engine/core/component.hpp"

//temp
#include "engine/render/render_engine.hpp"
#include "engine/scenes/scene_graph.hpp"


// to achieve at least something in MY word
// you HAVE TO inherit from THIS class
class BaseScene{
    protected:
        SceneGraph scene_graph;
        std::list<SceneNode*> garbage;
        BaseScene();
        ~BaseScene();
    public:
    
    //Engine purpose function
    //Override only if you REALLY understand what is going ond
    virtual void update(const float);
    //Engine purpose function
    //Override only if you REALLY understand what is going on
    virtual void render();
    
    virtual void on_update(const float)=0;
    virtual void on_init()=0;
    // ALL PROCESSORS INITIALIZATIONS SHOULD BE DONE HERE
    virtual void on_start()=0;
    virtual void on_destroy()=0;


    void introduce(SceneNode*);
    //WARNNING!
    //mark as garbage an ALREADY "destroy()-ed" object
    void mark_garbage(SceneNode*);
    bool has_grabage(){return !garbage.empty();}
    void clear_garbage();


};

#endif