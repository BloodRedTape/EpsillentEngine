#include "ui/ui_controller.hpp"
#include <queue>
#include "utils/debug.hpp"


UIController::UIController()
{
    on_init();
}
UIController::~UIController(){
    on_destroy();
    for(View *v: root){
        delete v;
    }
}

void UIController::update(float dt){
    for(View *v: root)
        v->update(dt);
    on_update(dt);
}

void UIController::render(){
    for(View *v: root)
        v->render();
}