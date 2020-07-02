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

class Renderer2D{
    private:
        

    public:
        Renderer2D(const Renderer2D&)=delete;
        Renderer2D& operator=(const Renderer2D&)=delete;


        Renderer2D();
        ~Renderer2D();

        void render();

};




#endif