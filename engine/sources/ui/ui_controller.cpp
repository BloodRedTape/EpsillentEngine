#include "ui/ui_controller.hpp"
#include <queue>
#include "utils/debug.hpp"


UIController::UIController():
    root(nullptr)
{}

void UIController::update(float dt){
    ASSERT_ERROR(root,"UIController has to provide a root View in order to display ui"); 
    root->update(dt);
}

void UIController::render(){
    root->render();
}