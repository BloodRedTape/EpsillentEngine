#include "engine.hpp"


Mainframe* Engine::mainframe = nullptr;
RenderEngine* Engine::render_engine = nullptr;
DisplayServer* Engine::display_server = nullptr;  //FOR now this thing is not working

SceneManager* Engine::scene_manager = nullptr;


const sf::VideoMode Engine::k_video_mode = sf::VideoMode(1280,720);  //better window creation
const char * Engine::k_window_title = "Engine";

Engine::Engine(){

}

Engine::~Engine(){

}
void Engine::init(){
    mainframe = new Mainframe();

    display_server = new DisplayServer(); //Yeah, required CUSTOM ALLOCATOR, but later
    render_engine = new RenderEngine();
    
    scene_manager = new SceneManager();
    Info("first init stage passed!");

    display_server->new_window(k_video_mode,k_window_title);
}


void Engine::main_cycle(){
    if(scene_manager->get_current_scene()==nullptr){
        Error("Engine:Create a scene and apply it via Engine::set_entry_scene(BaseScene* p_scene, const char* name)");
    }
    sf::Clock n;
    Info("enter main loop");
    while(1){
        mainframe->compute();
        Info("1");
        std::cout << std::to_string(n.getElapsedTime().asMicroseconds())<<std::endl;
        n.restart();
    }
}

void Engine::set_entry_scene(BaseScene* p_scene, const char* name){
    scene_manager->introduce_scene(name,p_scene,true);
}


void Engine::shutdown(){
    delete scene_manager;
    delete render_engine;
    delete display_server;
    delete mainframe;
}

