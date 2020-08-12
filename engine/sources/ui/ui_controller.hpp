#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ui/view.hpp"
#include <vector>
class UILayer;

class UIController{
protected:
    std::vector<View*> root;
    friend class UILayer;
private:
    void update(float dt);
    void render();
public:
    UIController();
    virtual ~UIController();

    virtual void on_init(){};
    virtual void on_update(float dt){};
    virtual void on_destroy(){};
};

#endif
