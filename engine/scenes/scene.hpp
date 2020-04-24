#ifndef SCENE_H
#define SCENE_H

#include "engine/core/component.hpp"

//temp
#include "engine/render/render_engine.hpp"


// to achieve at least something in my word
// you HAVE TO inherit from THIS class
class BaseScene{
    protected:
        Cluster render;
        Cluster collidable;
        Cluster triggerable; 
        RenderCluster m_render_cluster;
        BaseScene();
        ~BaseScene();
    public:
        RenderCluster& get_redner_cluster(){
            return m_render_cluster;
        }
    

    virtual void init()=0;
    // ALL PROCESSORS INITIALIZATIONS SHOULD BE DONE HERE
    virtual void start()=0;
    virtual void destroy()=0;


};

#endif