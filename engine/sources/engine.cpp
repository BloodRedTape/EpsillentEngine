#include "engine.hpp"
#include "platform/platform.hpp"
#include "scenes/game_layer.hpp"
#include "ui/ui_layer.hpp"
#include "core/math/random.hpp"
#include "utils/debug.hpp"
#include "utils/assets_manager.hpp"
std::atomic<bool> Engine::running;
std::mutex Engine::mutex;
DrawCallInterface* Engine::draw_call_interface = nullptr;
Input *Engine::input = nullptr;
UILayer *Engine::ui = nullptr;

LayerStack* Engine::layer_stack = nullptr;
sf::Clock Engine::time;

bool Engine::_show_fps = false;


const sf::VideoMode Engine::k_video_mode = sf::VideoMode(1280,720);  //better window creation

Engine* Engine::smp_singleton = nullptr;

Engine::Engine(){
    if(smp_singleton==nullptr){
        smp_singleton=this;
        Info("Engine: created");
    }else{
        Warning("Engine: created messy object");
    }
    sf::String string;
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

void Engine::init(const EngineProperties& props){
    time.restart();
    ASSERT_WARRNING(smp_singleton==this,"Engine: can't init from non-creator instance");
    Platform::init();
    



    DisplayServer::initialize(&mutex, props.mode, props.window_title.toAnsiString().c_str(), props.window_style);
        
    if(props.frame_rate_limit>0)
        DisplayServer::set_frame_rate_limit(props.frame_rate_limit);
    _show_fps = props.show_fps;

    draw_call_interface = new DrawCallInterface(DisplayServer::mp_display_target);
    
    input = new Input(DisplayServer::mp_display_target);

    SceneManager::initialize(&mutex);
    
    layer_stack = new LayerStack();

    layer_stack->push_layer(new GameLayer);


    Random::seed(time.getElapsedTime().asMilliseconds());
    Info("Engine: init took " + ARG(time.getElapsedTime().asSeconds()) + " seconds");
}

void Engine::shutdown(){
    ASSERT_WARRNING(smp_singleton==this,"Engine: can't shut down from non-creator instance");
    delete layer_stack;
    SceneManager::finalize();
    delete draw_call_interface;
    AssetsManager::clear();
    DisplayServer::finalize();
    Info("Engine: shuted down");
}


void Engine::UpdateLoop(){
    sf::Clock n;
    float frame_time = 0;
    float fps;
    while(running){
        Random::seed(time.getElapsedTime().asMilliseconds()*reinterpret_cast<unsigned long long>(SceneManager::get_current_scene()));

        for(auto itr = layer_stack->begin(); itr!=layer_stack->end();itr++){
            (*itr)->on_update(frame_time);
        }

        frame_time=n.getElapsedTime().asSeconds();
        fps = 1/frame_time;
        n.restart();

        Profiling(std::string("UpdateLoop :")+std::to_string(frame_time)+" ms \t\t| fps:" + std::to_string(fps));
    }
    
}
void Engine::RenderLoop(){
    sf::Clock n;
    float fps = 0;
    float frame_time = 0;

    sf::Font debug_font;
    debug_font.loadFromFile("resources/mont.otf");
    
    sf::Text debug_info;
    debug_info.setFont(debug_font);
    debug_info.setFillColor(sf::Color::Green);

    while(running){
        Engine::get_singleton()->handle_events(*DisplayServer::mp_display_target);

        DrawCallInterface::clear();
        
        for(auto itr = layer_stack->begin(); itr != layer_stack->end(); itr++){
            mutex.lock();
            (*itr)->on_render();
            mutex.unlock();
        }

        if(_show_fps){
            debug_info.setString("fps: " + std::to_string(fps));
            DrawCallInterface::draw(debug_info);
        }

        DrawCallInterface::swap_buffers();

        frame_time = n.getElapsedTime().asSeconds();
        fps = 1/frame_time;
        n.restart();

        Profiling(std::string("RenderLoop :")+std::to_string(frame_time)+" ms \t\t| fps:" + std::to_string(fps));
    }
}

void Engine::start(){
    running = true;
    ASSERT_ERROR(SceneManager::get_current_scene(),"Engine:Create a scene and apply it via Engine::set_entry_scene(BaseScene* p_scene, const char* name)")
    std::thread update(&Engine::UpdateLoop);
    update.detach();
    RenderLoop();
}

void Engine::stop(){
    running = false;
}

void Engine::set_entry_scene(BaseScene* p_scene, const char* name){
    SceneManager::introduce_scene(name,p_scene,true);
}


void Engine::set_ui_controller(UIController* c){
    if(!ui){
        ui = new UILayer;
        layer_stack->push_layer(ui);
    }
    ui->set_controller(c);
}

