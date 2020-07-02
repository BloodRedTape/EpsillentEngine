#ifndef LAYER_STACK_H
#define LAYER_STACK_H

#include <vector>
#include "engine/core/layer.hpp"


class LayerStack{
private:
    std::vector<Layer*> layers;
public:
    LayerStack();
    ~LayerStack();

    void push_layer(Layer*);
    void pop_layer();

    std::vector<Layer*>::iterator begin(){return layers.begin();}
    std::vector<Layer*>::iterator end(){return layers.end();}

};

#endif