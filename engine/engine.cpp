#include "engine.hpp"
#include "platform/platform.hpp"
#include "engine/scenes/game_layer.hpp"

std::atomic<bool> Engine::running;
std::mutex Engine::mutex;
Mainframe* Engine::mainframe = nullptr;
RenderEngine* Engine::render_engine = nullptr;
DisplayServer* Engine::display_server = nullptr;  //FOR now this thing is not working

SceneManager* Engine::scene_manager = nullptr;

LayerStack* Engine::layer_stack = nullptr;

bool Engine::_show_fps = false;


const sf::VideoMode Engine::k_video_mode = sf::VideoMode(1280,720);  //better window creation
const char * Engine::k_window_title = "Engine";

Engine* Engine::smp_singleton = nullptr;

Engine::Engine(){
    if(smp_singleton==nullptr){
        smp_singleton=this;
        Info("Engine: created");
    }else{
        Warning("Engine: created messy object");
    }
}

Engine::~Engine(){

}

void Engine::handle_events(sf::RenderWindow &window){
    sf::Event event;
    while(window.pollEvent(event)){
        switch (event.type)
        {
        case sf::Event::Closed:
            running = false;
            break;
        
        default:
            break;
        }
    }

}

void Engine::init(){
    if(smp_singleton==this){
        Platform::init();
        mainframe = new Mainframe();

        display_server = new DisplayServer(mutex); //Yeah, required CUSTOM ALLOCATOR, but later
        
        render_engine = new RenderEngine();
        
        scene_manager = new SceneManager(mutex);
        
        layer_stack = new LayerStack();

        layer_stack->push_layer(new GameLayer);

        display_server->init_window(k_video_mode,k_window_title);
        
        display_server->set_frame_rate_limit(60);
        Info("Engine: inited");
    }else{
        Warning("Engine: can't init from non-creator instance");
    }
}

void Engine::shutdown(){
    if(smp_singleton==this){
        delete layer_stack;
        delete scene_manager;
        delete render_engine;
        delete display_server;
        delete mainframe;
        Info("Engine: shuted down");
    }else{
        Warning("Engine: can't shut down from non-creator instance");
    }
}


void Engine::UpdateLoop::operator()(){
    sf::Clock n;
    float frame_time = 0;
    float fps;
    while(running){
        
        Engine::get_singleton()->handle_events(*DisplayServer::get_singleton()->mp_display_target);

        for(auto itr = layer_stack->begin(); itr!=layer_stack->end();itr++){
            (*itr)->on_update(frame_time);
        }

        frame_time=n.getElapsedTime().asSeconds();
        fps = 1/frame_time;
        n.restart();

        Profiling(std::string("UpdateLoop :")+std::to_string(frame_time)+" ms \t\t| fps:" + std::to_string(fps));
    }
    
}
void Engine::RenderLoop::operator()(){
    sf::Clock n;
    float fps = 0;
    float frame_time = 0;

    sf::Font debug_font;
    debug_font.loadFromFile("resources/mont.otf");
    
    sf::Text debug_info;
    debug_info.setFont(debug_font);
    debug_info.setFillColor(sf::Color::Green);

    while(running){
        display_server->clear_display();
        
        for(auto itr = layer_stack->begin(); itr != layer_stack->end(); itr++){
            mutex.lock();
            (*itr)->on_render();
            mutex.unlock();
        }

        if(_show_fps){
            debug_info.setString("fps: " + std::to_string(fps));
            render_engine->render(debug_info);
        }

        display_server->swap_buffers();

        frame_time = n.getElapsedTime().asSeconds();
        fps = 1/frame_time;
        n.restart();

        Profiling(std::string("RenderLoop :")+std::to_string(frame_time)+" ms \t\t| fps:" + std::to_string(fps));
    }
}

void Engine::start(){
    running = true;

    if(scene_manager->get_current_scene()==nullptr){
        Error("Engine:Create a scene and apply it via Engine::set_entry_scene(BaseScene* p_scene, const char* name)");
    }
    std::thread update{UpdateLoop()};
    update.detach();
    RenderLoop render;
    render();
}

void Engine::stop(){
    running = false;
}

void Engine::set_entry_scene(BaseScene* p_scene, const char* name){
    scene_manager->introduce_scene(name,p_scene,true);
}


