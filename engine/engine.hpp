#ifndef ENGINE
#define ENGINE
#include "main/main.hpp"
#include "core/typedefs.hpp"

#include "physics/physics_engine.hpp"
#include "render/render_engine.hpp"
#include "servers/display_server.hpp"
#include "utils/debug.hpp"
#include "scenes/scene_manager.hpp"
#include "core/mainframe.hpp"


class Engine{
    private:
        static Mainframe* mainframe;
        static RenderEngine* render_engine;
        static DisplayServer* display_server;  //FOR now this thing is not working

        static SceneManager* scene_manager;


        static const sf::VideoMode k_video_mode;  //better window creation
        static const char * k_window_title;
    public:
        Engine();
        ~Engine();
        
        void init();
        void shutdown();
        // TODO engine set window config
        void main_cycle();
        void set_entry_scene(BaseScene*, const char* name);


};




#endif