#ifndef GAME_LAYER_H
#define GAME_LAYER_H

#include "config/config.hpp"
#include "core/layer.hpp"

class ENGINE_API GameLayer: public Layer{
private:

public:
    GameLayer();
    ~GameLayer();
    void on_render()override;
    void on_update(float dt)override;
    void on_detach()override;
};

#endif