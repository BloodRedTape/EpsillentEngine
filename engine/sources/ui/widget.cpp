#include "ui/widget.hpp"


void Widget::update(float dt){
    for(Widget *w: children){
        w->update(dt);
    }
    on_update(dt);
}

void Widget::render(std::queue<Widget*>& queue){
    for(Widget *w: children){
        queue.push(w);
    }
}