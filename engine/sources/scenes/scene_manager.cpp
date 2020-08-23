#include "scenes/scene_manager.hpp"
#include "utils/debug.hpp"

std::mutex *SceneManager::p_sync_mutex = nullptr;
BaseScene *SceneManager::p_current_scene = nullptr;
std::unordered_map<std::string, std::unique_ptr<BaseScene>> SceneManager::scenes;


void SceneManager::initialize(std::mutex *p_sync){
    p_sync_mutex = p_sync;
}

void SceneManager::finalize(){
    scenes.clear();
    Info("SceneManager: finalized");
}


void SceneManager::update_scene(const float dt){
    //most probably here input will be handled
    p_current_scene->on_update(dt);
    p_current_scene->update(dt);
    
}

void SceneManager::render_scene(){
    p_current_scene->render();
}

void SceneManager::clean_scene_garbage(){
    if(p_current_scene->has_grabage()){
        std::lock_guard<std::mutex> lock(*p_sync_mutex);
        p_current_scene->clear_garbage();
    }
}


void SceneManager::introduce_scene(const std::string& scene_name, BaseScene* p_scene, bool set){
    ASSERT_ERROR(p_sync_mutex,"SceneManager: has not been inited");
    p_sync_mutex->lock();
    scenes.insert(std::pair<std::string, std::unique_ptr<BaseScene>>(scene_name,p_scene)); 
    if(set){
        p_current_scene=p_scene;
    }
    p_sync_mutex->unlock();
    if(set){
        p_current_scene=p_scene;
        p_scene->on_introduce();
        p_scene->on_start();
    }
}



void SceneManager::substract_scene(const std::string& name){
    ASSERT_ERROR(p_sync_mutex,"SceneManager: has not been inited");
    std::lock_guard<std::mutex> lock(*p_sync_mutex);
    std::unordered_map<std::string, std::unique_ptr<BaseScene>>::iterator map_itr = scenes.find(name);

    ASSERT_ERROR(map_itr!=scenes.end(),"SceneManager: trying to substract scene that wasn't introuduced or doesn't exist");
    ASSERT_ERROR(map_itr->second.get()!=p_current_scene,"SceneManager: trying to substract current scene");
    
    scenes.erase(map_itr);

}

BaseScene* SceneManager::get_scene(const std::string& name){
    ASSERT_ERROR(p_sync_mutex,"SceneManager: has not been inited");
    std::unordered_map<std::string, std::unique_ptr<BaseScene>>::iterator map_itr = scenes.find(name);
    ASSERT_ERROR(map_itr!=scenes.end(),"SceneManager: trying to substract scene that wasn't introuduced or doesn't exist");
    
    return map_itr->second.get();
}

//IMPLEMENT TO ASSIGN CLUSTERS TO COMPONENTS INSTEAD OF INF FETCH
void SceneManager::set_scene(const std::string& name){
    ASSERT_ERROR(p_sync_mutex,"SceneManager: has not been inited");
    std::lock_guard<std::mutex> lock(*p_sync_mutex);
    std::unordered_map<std::string, std::unique_ptr<BaseScene>>::iterator map_itr = scenes.find(name);
    ASSERT_ERROR(map_itr!=scenes.end(),"SceneManager: trying to substract scene that wasn't introuduced or doesn't exist");
    ASSERT_WARRNING(map_itr->second.get()!=p_current_scene,"SceneManager: trying to set already established scene");

    p_current_scene = map_itr->second.get();
    p_current_scene->on_start();
}


BaseScene* SceneManager::get_current_scene(){
    ASSERT_ERROR(p_sync_mutex,"SceneManager: has not been inited");
    
    return p_current_scene;
}