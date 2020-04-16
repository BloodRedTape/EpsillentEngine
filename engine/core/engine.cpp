#include "engine/core/engine.hpp"
#include "engine/utils/debug.hpp"

Engine* Engine::smp_singleton = nullptr;

Engine::Engine(){
    if(smp_singleton==nullptr){
        smp_singleton=this;
        Info("Engine: created");
    }else{
        Warning("Engine: created messy instance");
    }        
}

Engine::~Engine(){
    Info("Engine: shutting down Game engine...");

    // code to stop all of running processes 

    Info("Engine: exit");
    std::exit(0);
}



