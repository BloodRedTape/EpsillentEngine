#ifndef ENGINE
#define ENGINE

#include "config/config.hpp"
#include "core/typedefs.hpp"

#include "physics/physics_engine.hpp"
#include "render/renderer_2d.hpp"
#include "servers/display_server.hpp"
#include "utils/debug.hpp"
#include "scenes/scene_manager.hpp"
#include "core/mainframe.hpp"
#include "core/layer_stack.hpp"
#include "render/draw_call.hpp"
#include "platform/input.hpp"
#include <thread>
#include <mutex>
#include <atomic>
#include "SFML/System.hpp"
#include "SFML/Window/WindowStyle.hpp"



struct EngineProperties{
    sf::String window_title;
    // if set to sf::Style::Fullscreen, width and heigth properties are ignored
    uint32 window_style;
    uint32 window_width;
    uint32 window_heigth;
    // no fps limit with 0 value
    uint32 frame_rate_limit;
    bool show_fps;
    EngineProperties():
        window_title("Game"), 
        window_style(sf::Style::Default), window_width(1280), window_heigth(720), frame_rate_limit(0), show_fps(false)
    {}
};


class ENGINE_API Engine{
    private:
        static std::atomic<bool> running;
        static std::mutex mutex;
        static Mainframe* mainframe;
        static DrawCallInterface* draw_call_interface;
        static DisplayServer* display_server;  //FOR now this thing is not working

        static SceneManager* scene_manager;
        static LayerStack* layer_stack;
        static const sf::VideoMode k_video_mode;  //better window creation
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

        void handle_events(sf::RenderWindow& window);

    public:
        Engine();
        ~Engine();
        static _ALWAYS_INLINE_ Engine* get_singleton(){return smp_singleton;}
        void init(const EngineProperties& props);
        void shutdown();
        // TODO engine set window config
        void start();
        void stop();
        void set_entry_scene(BaseScene*, const char* name);


};




#endif