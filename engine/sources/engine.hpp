#ifndef ENGINE
#define ENGINE

#include "config/config.hpp"
#include "core/typedefs.hpp"

#include "physics/physics_engine.hpp"
#include "render/renderer_2d.hpp"
#include "servers/display_server.hpp"
#include "utils/debug.hpp"
#include "scenes/scene_manager.hpp"
#include "core/layer_stack.hpp"
#include "render/draw_call.hpp"
#include "platform/input.hpp"
#include <thread>
#include <mutex>
#include <atomic>
#include "SFML/System.hpp"
#include "SFML/System/Sleep.hpp"
#include "SFML/Window/WindowStyle.hpp"
#include "ui/ui_controller.hpp"
#include "ui/ui_layer.hpp"

using sf::sleep;

struct EngineProperties{
    sf::String window_title;
    uint32 window_style;
    sf::VideoMode mode;
    // no fps limit with 0 value
    uint32 frame_rate_limit;
    bool show_fps;
    EngineProperties():
        window_title("Game"), 
        window_style(sf::Style::Default), mode(1280,720), frame_rate_limit(0), show_fps(false)
    {}
};


class ENGINE_API Engine{
    private:
        static std::atomic<bool> running;
        static std::thread *update_thread;
        static std::mutex mutex;
        static DrawCallInterface* draw_call_interface;
        static Input* input;
        static LayerStack* layer_stack;
        static const sf::VideoMode k_video_mode;  //better window creation
        static Engine *smp_singleton;
        static sf::Clock time;
        static float dt;
        static bool _show_fps;
        static std::pair<std::string,BaseScene *>entry;
    private:
        static void RenderLoop();
        static void UpdateLoop();
        void handle_events(sf::RenderWindow& window);
    public:
        Engine();
        ~Engine();
        static _ALWAYS_INLINE_ Engine* get_singleton(){return smp_singleton;}
        void initialize(const EngineProperties& props);
        void finalize();
        void start();
        void stop();
        void set_entry_scene(BaseScene*, const char* name);

        float delta_time();
};




#endif