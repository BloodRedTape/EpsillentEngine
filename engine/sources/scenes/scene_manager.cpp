#include "scenes/scene_manager.hpp"
#include "utils/debug.hpp"

std::mutex *SceneManager::p_sync_mutex = nullptr;
BaseScene *SceneManager::p_current_scene = nullptr;
std::unordered_map<std::string, BaseScene *> SceneManager::scenes;


void SceneManager::initialize(std::mutex *p_sync){
    p_sync_mutex = p_sync;
}

void SceneManager::finalize(){
    for(auto itr = scenes.begin(); itr!= scenes.end(); itr++){
        itr->second->on_destroy();
        itr->second->clear();
        itr->second->clear_garbage();
        delete itr->second;
        Info("SceneManager: deleted \""+ itr->first + "\" scene");
    }
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


void SceneManager::introduce_scene(const std::string& scene_name, BaseScene* p_scene, bool is_displayable = false){
    ASSERT_ERROR(p_sync_mutex,"SceneManager: has not been inited");
    std::lock_guard<std::mutex> lock(*p_sync_mutex);
    scenes.insert(std::pair<std::string, BaseScene*>(scene_name,p_scene)); 
    if(is_displayable){
        p_current_scene=p_scene;
        p_scene->on_init();
        p_scene->on_start();
    }
}



void SceneManager::substract_scene(const std::string& name){
    ASSERT_ERROR(p_sync_mutex,"SceneManager: has not been inited");
    std::lock_guard<std::mutex> lock(*p_sync_mutex);
    std::unordered_map<std::string, BaseScene*>::iterator map_itr = scenes.find(name);
    if(map_itr==scenes.end()){
        Error("SceneManager: trying to substract scene that wasn't introuduced or doesn't exist");
    }else if(map_itr->second==p_current_scene){
        Error("SceneManager: trying to substract current scene (Possible processor-cluster pipeline corruption)");
    }else{
        map_itr->second->on_destroy();
        scenes.erase(map_itr);
    }
}

BaseScene* SceneManager::get_scene(const std::string& name){
    ASSERT_ERROR(p_sync_mutex,"SceneManager: has not been inited");
    std::unordered_map<std::string, BaseScene*>::iterator map_itr = scenes.find(name);
    if(map_itr==scenes.end()){
        Error("SceneManager: trying to get scene that wasn't introuduced or doesn't exist");
        return nullptr; // it won't be returned Error() terminates runtime
    }else{
        return map_itr->second;
    }
}

//IMPLEMENT TO ASSIGN CLUSTERS TO COMPONENTS INSTEAD OF INF FETCH
void SceneManager::set_scene(const std::string& name){
    ASSERT_ERROR(p_sync_mutex,"SceneManager: has not been inited");
    std::lock_guard<std::mutex> lock(*p_sync_mutex);
    std::unordered_map<std::string, BaseScene*>::iterator map_itr = scenes.find(name);
    if(map_itr==scenes.end()){
        Error("SceneManager: trying to set scene that wasn't introuduced or doesn't exist");
    }else if(map_itr->second==p_current_scene){
        Warning("SceneManager: trying to set already established scene");
    }else{
        p_current_scene = map_itr->second;
        p_current_scene->on_start();
    }

}


BaseScene* SceneManager::get_current_scene(){
    if(p_sync_mutex){
        return p_current_scene;
    }else{
        Error("SceneManager: has not been inited");
        return nullptr;
    }
}