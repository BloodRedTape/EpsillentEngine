#ifndef SCENE_H
#define SCENE_H

#include "engine/core/component.hpp"

//temp
#include "engine/render/render_engine.hpp"
#include "engine/scenes/scene_graph.hpp"


// to achieve at least something in my word
// you HAVE TO inherit from THIS class
class BaseScene{
    protected:
        SceneGraph scene_graph;
        BaseScene();
        ~BaseScene();
    public:
    virtual void engine_update(const float);
    virtual void update(const float)=0;
    virtual void init()=0;
    // ALL PROCESSORS INITIALIZATIONS SHOULD BE DONE HERE
    virtual void start()=0;
    virtual void destroy()=0;


};

#endif