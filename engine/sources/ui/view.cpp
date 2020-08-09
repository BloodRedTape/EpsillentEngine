#include "ui/view.hpp"


void View::update(float dt){
    on_update(dt);
}

void View::render(){
    on_render();
}
