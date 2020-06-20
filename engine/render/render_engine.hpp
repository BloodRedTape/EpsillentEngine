#ifndef RENDER_H
#define RENDER_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "engine/core/typedefs.hpp"
//#include "engine/core/cluster.hpp"
#include "engine/servers/display_server.hpp"
#include "engine/core/processor.hpp"
//for a short time
#include <list>
typedef std::list<sf::Drawable*> RenderCluster;

class RenderEngine{
    private:
        static RenderEngine* smp_singleton;
        

    public:
        RenderEngine(const RenderEngine&)=delete;
        RenderEngine& operator=(const RenderEngine&)=delete;

        //!!!somewhen create a setup with EngineClusterSet!!!!!
        RenderEngine();
        ~RenderEngine();


        void render(sf::Drawable&, const sf::Transform&);


        _ALWAYS_INLINE_ static RenderEngine* get_singleton(){
            return smp_singleton;
        } 

};




#endif