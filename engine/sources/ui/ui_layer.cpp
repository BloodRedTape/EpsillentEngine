#include "ui/ui_layer.hpp"
#include "SFML/Graphics.hpp"
#include "render/draw_call.hpp"
#include "utils/debug.hpp"
#include "scenes/scene_manager.hpp"
UILayer::UILayer(){
    Info("UILayer: created");
}
UILayer::~UILayer(){
    Info("UILayer: destroyed");
}

void UILayer::on_render(){
    if(SceneManager::get_current_scene()->ui_controller())
        SceneManager::get_current_scene()->ui_controller()->render();
}

void UILayer::on_update(float dt){
    if(SceneManager::get_current_scene()->ui_controller())
        SceneManager::get_current_scene()->ui_controller()->update(dt);
}   
