#include "ui/ui_controller.hpp"
#include <queue>
#include "utils/debug.hpp"


UIController::UIController():
    root(nullptr)
{}

void UIController::update(float dt){
    ASSERT_ERROR(root,"UIController has to provide a root widget in order to display ui"); 
    root->update(dt);
}

void UIController::render(){
    std::queue<Widget*> render_queue;
    render_queue.push(root);
    while (!render_queue.empty())
    {
        Widget* w = render_queue.front();
        render_queue.pop();
        w->render(render_queue);
        w->on_render();
    }
    
}