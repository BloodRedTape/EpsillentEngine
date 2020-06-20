#ifndef ENGINE
#define ENGINE
#include "core/typedefs.hpp"

#include "physics/physics_engine.hpp"
#include "render/render_engine.hpp"
#include "servers/display_server.hpp"
#include "utils/debug.hpp"
#include "scenes/scene_manager.hpp"
#include "core/mainframe.hpp"

#include <thread>
#include <mutex>
#include <atomic>

class Engine{
    private:
        static std::atomic<bool> running;
        static std::mutex mutex;
        static Mainframe* mainframe;
        static RenderEngine* render_engine;
        static DisplayServer* display_server;  //FOR now this thing is not working

        static SceneManager* scene_manager;


        static const sf::VideoMode k_video_mode;  //better window creation
        static const char * k_window_title;
        static Engine *smp_singleton;
        
        static bool _show_fps;
        class RenderLoop{
            public:
                void operator()();
        };

        class UpdateLoop{
            public:
                void operator()();
        };

    public:
        Engine();
        ~Engine();
        static _ALWAYS_INLINE_ Engine* get_singleton(){return smp_singleton;}
        void init();
        void shutdown();
        // TODO engine set window config
        void start();
        void stop();
        void set_entry_scene(BaseScene*, const char* name);

        void show_fps(bool b){_show_fps=b;};


};




#endif