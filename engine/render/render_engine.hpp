#ifndef RENDER_H
#define RENDER_H

#include <memory>
#include <SFML/Graphics.hpp>
//#include "engine/core/cluster.hpp"
#include "engine/servers/display_server.hpp"
#include "engine/core/processor.hpp"
//for a short time
#include <list>
typedef sf::Drawable Drawable;
typedef std::list<Drawable*> RenderCluster;

class RenderEngine: public Processor{
    private:
        static RenderEngine* smp_singleton;
        RenderCluster* mp_cluster;
        Cluster clust;
        

    public:
        RenderEngine(const RenderEngine&)=delete;
        RenderEngine& operator=(const RenderEngine&)=delete;

        //!!!somewhen create a setup with EngineClusterSet!!!!!
        RenderEngine();
        ~RenderEngine();


        void process();

        //setup a cluster for processing
        void set_cluster(RenderCluster*);

        static RenderEngine* get_singleton(){return smp_singleton;} 

};




#endif