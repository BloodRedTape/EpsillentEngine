#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <map>
#include <string>
#include "engine/core/typedefs.hpp"
#include "engine/scenes/scene.hpp"



// KING OF THE ENGINE
class SceneManager{
    private:
        static SceneManager* smp_singleton;
        BaseScene* current_scene;
        std::map<std::string, BaseScene*> scenes;

    public:
        SceneManager();
        ~SceneManager();

        _ALWAYS_INLINE_ SceneManager* get_singleton(){
            return smp_singleton;
        }
        BaseScene* get_current_scene();
        BaseScene* get_scene(const std::string& );
        void introduce_scene(const std::string&, BaseScene*, bool);
        void set_scene(const std::string&);
        void substract_scene(const std::string&);

};


#endif