#include "scenes/game_layer.hpp"
#include "scenes/scene_manager.hpp"

void GameLayer::on_render(){
    SceneManager::get_singleton()->render_scene();
}

void GameLayer::on_update(float dt){
    SceneManager::get_singleton()->update_scene(dt);
    SceneManager::get_singleton()->clean_scene_garbage();
}