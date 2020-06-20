#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <map>
#include <string>
#include "engine/core/typedefs.hpp"
#include "engine/scenes/scene.hpp"
#include <mutex>


// KING OF THE ENGINE
class SceneManager{
    private:
        static SceneManager* smp_singleton;
        std::mutex &mutex;
        BaseScene* current_scene;
        std::map<std::string, BaseScene*> scenes;

    public:
        SceneManager(std::mutex&);
        ~SceneManager();

        static _ALWAYS_INLINE_ SceneManager* get_singleton(){
            return smp_singleton;
        }
        _ALWAYS_INLINE_ BaseScene* get_current_scene(){
            return current_scene;
        }
        void update_scene(const float dt);
        void render_scene();
        void clean_scene_garbage();
        BaseScene* get_scene(const std::string& );
        void introduce_scene(const std::string&, BaseScene*, bool);
        void set_scene(const std::string&);
        void substract_scene(const std::string&);

};


#endif