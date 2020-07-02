#include "engine/scenes/scene_manager.hpp"
#include "engine/utils/debug.hpp"

SceneManager* SceneManager::smp_singleton = nullptr;

SceneManager::SceneManager(std::mutex& mtx):
    mutex(mtx)
{
    if(smp_singleton==nullptr){
        smp_singleton=this;
        Info("SceneManager: created");
    }else{
        Warning("SceneManager: created messy object");
    }
}

SceneManager::~SceneManager(){
    Info("SceneManager: deleted");
}


void SceneManager::update_scene(const float dt){
    //most probably here input will be handled
    current_scene->on_update(dt);
    current_scene->update(dt);
    
}

void SceneManager::render_scene(){
    current_scene->render();
}

void SceneManager::clean_scene_garbage(){
    if(current_scene->has_grabage()){
        std::lock_guard<std::mutex> lock(smp_singleton->mutex);
        current_scene->clear_garbage();
    }
}


//IMPLEMENT TO ASSIGN CLUSTERS TO COMPONENTS INSTEAD OF INF FETCH
void SceneManager::introduce_scene(const std::string& scene_name, BaseScene* p_scene, bool is_displayable = false){
    ASSERT_ERROR(smp_singleton,"SceneManager: has not been inited");
    std::lock_guard<std::mutex> lock(smp_singleton->mutex);
    smp_singleton->scenes.insert(std::pair<std::string, BaseScene*>(scene_name,p_scene)); 
    if(is_displayable){
        smp_singleton->current_scene=p_scene;
        p_scene->on_init();
        p_scene->on_start();
    }
}



void SceneManager::substract_scene(const std::string& name){
    ASSERT_ERROR(smp_singleton,"SceneManager: has not been inited");
    std::lock_guard<std::mutex> lock(smp_singleton->mutex);
    std::map<std::string, BaseScene*>::iterator map_itr = smp_singleton->scenes.find(name);
    if(map_itr==smp_singleton->scenes.end()){
        Error("SceneManager: trying to substract scene that wasn't introuduced or doesn't exist");
    }else if(map_itr->second==smp_singleton->current_scene){
        Error("SceneManager: trying to substract current scene (Possible processor-cluster pipeline corruption)");
    }else{
        map_itr->second->on_destroy();
        smp_singleton->scenes.erase(map_itr);
    }
}

BaseScene* SceneManager::get_scene(const std::string& name){
    ASSERT_ERROR(smp_singleton,"SceneManager: has not been inited");
    std::map<std::string, BaseScene*>::iterator map_itr = smp_singleton->scenes.find(name);
    if(map_itr==smp_singleton->scenes.end()){
        Error("SceneManager: trying to get scene that wasn't introuduced or doesn't exist");
        return nullptr; // it won't be returned Error() terminates runtime
    }else{
        return map_itr->second;
    }
}

//IMPLEMENT TO ASSIGN CLUSTERS TO COMPONENTS INSTEAD OF INF FETCH
void SceneManager::set_scene(const std::string& name){
    ASSERT_ERROR(smp_singleton,"SceneManager: has not been inited");
    std::lock_guard<std::mutex> lock(smp_singleton->mutex);
    std::map<std::string, BaseScene*>::iterator map_itr = smp_singleton->scenes.find(name);
    if(map_itr==smp_singleton->scenes.end()){
        Error("SceneManager: trying to set scene that wasn't introuduced or doesn't exist");
    }else if(map_itr->second==smp_singleton->current_scene){
        Warning("SceneManager: trying to set already established scene");
    }else{
        smp_singleton->current_scene = map_itr->second;
        smp_singleton->current_scene->on_start();
    }

}


BaseScene* SceneManager::get_current_scene(){
    if(smp_singleton){
        return smp_singleton->current_scene;
    }else{
        Error("SceneManager: has not been inited");
        return nullptr;
    }
}