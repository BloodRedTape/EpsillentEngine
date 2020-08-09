#include "ui/ui_controller.hpp"
#include <queue>
#include "utils/debug.hpp"


UIController::UIController():
    root(nullptr)
{
    on_init();
}
UIController::~UIController(){
    on_destroy();
    ASSERT_ERROR(root, "UIController has to provide a root View in order to display ui");
    delete root;
}

void UIController::update(float dt){
    ASSERT_ERROR(root,"UIController has to provide a root View in order to display ui"); 
    root->update(dt);
    on_update(dt);
}

void UIController::render(){
    root->render();
}