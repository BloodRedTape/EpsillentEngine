#include "ui/widget.hpp"


void Widget::update(float dt){
    on_update(dt);
}

void Widget::render(){
    on_render();
}
