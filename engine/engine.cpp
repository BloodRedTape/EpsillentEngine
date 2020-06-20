#include "engine.hpp"
#include <chrono>
#include "platform/platform.hpp"

std::atomic<bool> Engine::running;
std::mutex Engine::mutex;
Mainframe* Engine::mainframe = nullptr;
RenderEngine* Engine::render_engine = nullptr;
DisplayServer* Engine::display_server = nullptr;  //FOR now this thing is not working

SceneManager* Engine::scene_manager = nullptr;


const sf::VideoMode Engine::k_video_mode = sf::VideoMode(1280,720);  //better window creation
const char * Engine::k_window_title = "Engine";

Engine* Engine::instance = nullptr;

Engine::Engine(){
    if(instance==nullptr){
        instance=this;
        Info("Engine: created");
    }else{
        Warning("Engine: created messy object");
    }
}

Engine::~Engine(){

}
void Engine::init(){
    if(instance==this){
        Platform::init();
        mainframe = new Mainframe();

        display_server = new DisplayServer(mutex); //Yeah, required CUSTOM ALLOCATOR, but later
        
        render_engine = new RenderEngine();
        
        scene_manager = new SceneManager(mutex);
        

        display_server->init_window(k_video_mode,k_window_title);
        
        display_server->set_frame_rate_limit(60);
        Info("Engine: inited");
    }else{
        Warning("Engine: can't init from non-creator instance");
    }
}


void Engine::UpdateLoop::operator()(){
    sf::Clock n;

    float frameTime;
    while(instance->running){
        instance->scene_manager->update_scene(frameTime);
        instance->mainframe->compute();
        instance->scene_manager->clean_scene_garbage();
        frameTime=n.getElapsedTime().asSeconds();
        
        Info(std::string("    UpdateLoop")+std::to_string(n.getElapsedTime().asMicroseconds())+" ms | fps:" + std::to_string(1/n.getElapsedTime().asSeconds()));
        n.restart();
    }
    
}
void Engine::RenderLoop::operator()(){
    sf::Clock n;
    while(instance->running){
        instance->display_server->clear_display();
        instance->scene_manager->render_scene();
        instance->display_server->swap_buffers();
        Info(std::string("RenderLoop")+std::to_string(n.getElapsedTime().asMicroseconds())+" ms | fps:" + std::to_string(1/n.getElapsedTime().asSeconds()));
        n.restart();
    }
}

void Engine::start(){
    running = true;

    if(instance->scene_manager->get_current_scene()==nullptr){
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
    instance->scene_manager->introduce_scene(name,p_scene,true);
}


void Engine::shutdown(){
    if(instance==this){
        delete scene_manager;
        delete render_engine;
        delete display_server;
        delete mainframe;
        Info("Engine: shuted down");
    }else{
        Warning("Engine: can't shut down from non-creator instance");
    }
}

