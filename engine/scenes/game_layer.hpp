#ifndef GAME_LAYER_H
#define GAME_LAYER_H

#include "engine/core/layer.hpp"

class GameLayer: public Layer{
private:

public:
    void on_render()override;
    void on_update(float dt)override;
};

#endif