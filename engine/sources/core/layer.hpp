#ifndef LAYER_H
#define LAYER_H

#include "config/config.hpp"

class ENGINE_API Layer{
private:

public:
    Layer(){};
    virtual ~Layer(){};

    virtual void on_update(float dt){};
    virtual void on_render(){};

    virtual void on_attach(){};
    virtual void on_detach(){};

};

#endif