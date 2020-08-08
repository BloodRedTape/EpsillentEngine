#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <unordered_map>
#include <string>
#include "config/config.hpp"
#include "core/typedefs.hpp"
#include "scenes/scene.hpp"
#include <mutex>

class Engine;
class GameLayer;

class ENGINE_API SceneManager{
private:
    static std::mutex *p_sync_mutex;
    static BaseScene *p_current_scene;
    static std::unordered_map<std::string, BaseScene *> scenes;
private:
    friend class Engine;
    friend class GameLayer;

    static void initialize(std::mutex *p_sync);
    static void finalize();
    
    static void update_scene(const float dt);
    static void render_scene();
    static void clean_scene_garbage();
public:
    SceneManager() = default;
    ~SceneManager() = default;
    

    static BaseScene* get_scene(const std::string& );
    static void introduce_scene(const std::string&, BaseScene*, bool);
    static void set_scene(const std::string&);
    static void substract_scene(const std::string&);
    static BaseScene* get_current_scene();

};


#endif