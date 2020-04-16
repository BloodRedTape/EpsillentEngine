#ifndef ENGINE_H
#define ENGINE_H

#include "engine/core/os/time.hpp"

class Engine{
    private:
        static Engine * smp_singleton;
    
        float s_delta_time; 
        float s_frames_per_second;

    public:
        Engine();
        ~Engine();
        Engine* get_singleton(){return smp_singleton;}
        void off(){get_singleton()->~Engine();}
        float fps(){return get_singleton()->s_frames_per_second;}
        float delta_time(){return get_singleton()->s_delta_time;}
};

#endif