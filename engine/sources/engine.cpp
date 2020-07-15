#include "engine.hpp"
#include "platform/platform.hpp"
#include "scenes/game_layer.hpp"
#include "ui/ui_layer.hpp"
#include "core/math/random.hpp"

std::atomic<bool> Engine::running;
std::mutex Engine::mutex;
Mainframe* Engine::mainframe = nullptr;
DrawCallInterface* Engine::draw_call_interface = nullptr;
DisplayServer* Engine::display_server = nullptr;  //FOR now this thing is not working
Input *Engine::input = nullptr;
UILayer *Engine::ui = nullptr;
SceneManager* Engine::scene_manager = nullptr;

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
    


    mainframe = new Mainframe();

    display_server = new DisplayServer(mutex); //Yeah, required CUSTOM ALLOCATOR, but later
    if(props.window_style == sf::Style::Fullscreen){
        display_server->init_window(sf::VideoMode::getDesktopMode(),props.window_title.toAnsiString().c_str(),props.window_style);
    }else{
        display_server->init_window(sf::VideoMode(props.window_width,props.window_heigth),props.window_title.toAnsiString().c_str(),props.window_style);
    }
        
    if(props.frame_rate_limit>0)
        display_server->set_frame_rate_limit(props.frame_rate_limit);
    _show_fps = props.show_fps;

    draw_call_interface = new DrawCallInterface(display_server->mp_display_target);
    
    input = new Input(display_server->mp_display_target);

    scene_manager = new SceneManager(mutex);
    
    layer_stack = new LayerStack();

    layer_stack->push_layer(new GameLayer);
    ui = new UILayer;
    layer_stack->push_layer(ui);

    Random::seed(time.getElapsedTime().asMilliseconds());
    Info("Engine: init took " + ARG(time.getElapsedTime().asSeconds()) + " seconds");
}

void Engine::shutdown(){
    ASSERT_WARRNING(smp_singleton==this,"Engine: can't shut down from non-creator instance");
    delete layer_stack;
    delete scene_manager;
    delete draw_call_interface;
    delete display_server;
    delete mainframe;
    Info("Engine: shuted down");
}


void Engine::UpdateLoop::operator()(){
    sf::Clock n;
    float frame_time = 0;
    float fps;
    while(running){
        Random::seed(time.getElapsedTime().asMilliseconds()*reinterpret_cast<unsigned long long>(this));

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
        Engine::get_singleton()->handle_events(*DisplayServer::get_singleton()->mp_display_target);

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


void Engine::set_ui_controller(UIController* c){
    ui->set_controller(c);
}

