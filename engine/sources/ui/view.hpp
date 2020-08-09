#ifndef WIDGET_H
#define WIDGET_H

#include <vector>
#include <queue>

class UIController;

class View{
private:
    virtual void render();
    virtual void update(float dt);
    friend class UIController;
public:
    virtual ~View(){};

    virtual void on_render()=0;
    virtual void on_update(float dt)=0;
};




#endif