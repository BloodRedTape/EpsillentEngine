#include "engine/utils/debug.hpp"
#include "engine/render/render_engine.hpp"
#include "engine/servers/display_server.hpp"

RenderEngine* RenderEngine::smp_singleton = nullptr;

RenderEngine::RenderEngine():
    Processor(&clust)
{
    if(smp_singleton==nullptr){
        smp_singleton=this;
        Info("RenderEngine: created");
    }else{
        Warning("RenderEngine: created messy object");
    }
}
RenderEngine::~RenderEngine(){
    Info("RenderEngine: deleted");
}
void RenderEngine::set_cluster(RenderCluster* p_drawing_candidate){
    get_singleton()->mp_cluster=p_drawing_candidate;
}


void RenderEngine::process(){
    RenderWindow& r_render_window = DisplayServer::get_singleton()->get_display_target();
    r_render_window.clear();
    
    for(RenderCluster::iterator itr = get_singleton()->mp_cluster->begin(); itr!=get_singleton()->mp_cluster->end(); itr++){
        r_render_window.draw(**itr);
    }
    r_render_window.display();
}

/*
pastgen implementation
void RenderEngine::render(RenderWindow& r_render_window){
    r_render_window.clear();
    
    for(RenderCluster::iterator itr = get_singleton()->mp_cluster->begin(); itr!=get_singleton()->mp_cluster->end(); itr++){
        r_render_window.draw(**itr);
    }
    
   
    r_render_window.display();
}
*/