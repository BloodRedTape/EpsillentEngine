#ifndef ENGINE_H
#define ENGINE_H

#include "engine/core/typedefs.hpp"
#include "engine/core/os/time.hpp"

class Engine{
    private:
        static Engine * smp_singleton;
    
        float s_delta_time; 
        float s_frames_per_second;

    public:
        Engine();
        ~Engine();
        _ALWAYS_INLINE_ Engine* get_singleton(){
            return smp_singleton;
        }
        _ALWAYS_INLINE_ void off(){
            get_singleton()->~Engine();
        }
        _ALWAYS_INLINE_ float fps(){
            return get_singleton()->s_frames_per_second;
        }
        _ALWAYS_INLINE_ float delta_time(){
            return get_singleton()->s_delta_time;
        }
};

#endif