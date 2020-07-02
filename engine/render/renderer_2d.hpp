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

class Renderer2D{
    private:
        static Renderer2D* smp_singleton;
        

    public:
        Renderer2D(const Renderer2D&)=delete;
        Renderer2D& operator=(const Renderer2D&)=delete;

        //!!!somewhen create a setup with EngineClusterSet!!!!!
        Renderer2D();
        ~Renderer2D();


        void render(sf::Drawable&, const sf::Transform&);
        void render(sf::Drawable&);


        _ALWAYS_INLINE_ static Renderer2D* get_singleton(){
            return smp_singleton;
        } 

};




#endif