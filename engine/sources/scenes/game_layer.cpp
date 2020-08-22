#include "scenes/game_layer.hpp"
#include "scenes/scene_manager.hpp"

GameLayer::GameLayer(){
    Info("GameLayer: created");
}
GameLayer::~GameLayer(){
    Info("GameLayer: destroyed");
}

void GameLayer::on_render(){
    SceneManager::render_scene();
}

void GameLayer::on_update(float dt){
    SceneManager::update_scene(dt);
}
