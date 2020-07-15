#ifndef UI_LAYER_H
#define UI_LAYER_H

#include "config/config.hpp"
#include "core/layer.hpp"

class ENGINE_API UILayer: public Layer{
private:

public:
    void on_update(float dt);
    void on_render();
};

#endif