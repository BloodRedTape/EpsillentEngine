#include "engine/core/engine.hpp"
#include "engine/physics/physics_engine.hpp"
#include "engine/render/render_engine.hpp"
#include "engine/servers/display_server.hpp"
#include "engine/utils/debug.hpp"
#include "engine/scenes/scene_manager.hpp"
#include "engine/core/mainframe.hpp"


static Engine* engine = nullptr;
static Mainframe* mainframe = nullptr;
static RenderEngine* render_engine = nullptr;
static DisplayServer* display_server = nullptr;  //FOR now this thing is not working

static SceneManager* scene_manager = nullptr;


static const sf::VideoMode k_video_mode = sf::VideoMode(1280,720);  //better window creation
static const char * k_window_title = "OpenGL";


void init(){
    engine = new Engine();
    mainframe = new Mainframe();

    display_server = new DisplayServer(); //Yeah, required CUSTOM ALLOCATOR, but later
    render_engine = new RenderEngine();
    
    scene_manager = new SceneManager();
    Info("first init stage passed!");
}



void processors_init(){
    
}


int main(){             
    init();
    //scene_manager->introduce_scene("Main",new Scene(),true); 
    render_engine->set_cluster(&(scene_manager->get_current_scene()->get_redner_cluster())); 
    //display_server->set_display_targer(&display_target);
    

    sf::Clock n;
    while(1){
        mainframe->compute();
        std::cout << std::to_string(n.getElapsedTime().asMicroseconds())<<std::endl;
        n.restart();
    }
    
    
}



