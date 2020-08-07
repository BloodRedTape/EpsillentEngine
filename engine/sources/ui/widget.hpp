#ifndef WIDGET_H
#define WIDGET_H

#include <vector>
#include <queue>

class UIController;

class Widget{
private:
    std::vector<Widget*> children;
private:
    void render(std::queue<Widget*>&);
    void update(float dt);
    friend class UIController;
public:
    virtual ~Widget(){};

    virtual void on_render()=0;
    virtual void on_update(float dt)=0;
    void child_add(Widget*);
};




#endif