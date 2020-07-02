#include "engine/core/layer_stack.hpp"


LayerStack::LayerStack(){
}

LayerStack::~LayerStack(){
    for(auto itr = begin(); itr !=end(); itr++){
        delete *itr;
    }
}

void LayerStack::push_layer(Layer* layer){
    layers.push_back(layer);
}

void LayerStack::pop_layer(){
    
    delete *std::prev(layers.end());
    layers.pop_back();
}