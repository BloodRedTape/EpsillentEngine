#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <map>
#include <string>
#include "config/config.hpp"
#include "core/typedefs.hpp"
#include "scenes/scene.hpp"
#include <mutex>

class Engine;
class GameLayer;
// KING OF THE ENGINE
class ENGINE_API SceneManager{
private:
    static SceneManager* smp_singleton;
    std::mutex &mutex;
    BaseScene* current_scene;
    std::map<std::string, BaseScene*> scenes;

private:
    friend class Engine;
    friend class GameLayer;
    
    void update_scene(const float dt);
    void render_scene();
    void clean_scene_garbage();
public:
    SceneManager(std::mutex&);
    ~SceneManager();

    static _ALWAYS_INLINE_ SceneManager* get_singleton(){
        return smp_singleton;
    }
    

    static BaseScene* get_scene(const std::string& );
    static void introduce_scene(const std::string&, BaseScene*, bool);
    static void set_scene(const std::string&);
    static void substract_scene(const std::string&);
    static BaseScene* get_current_scene();

};


#endif