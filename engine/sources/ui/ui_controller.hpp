#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ui/view.hpp"

class UILayer;

class UIController{
protected:
    View* root;
    friend class UILayer;
public:
    UIController();
    virtual ~UIController() = default;
private:
    void update(float dt);
    void render();
};

#endif
