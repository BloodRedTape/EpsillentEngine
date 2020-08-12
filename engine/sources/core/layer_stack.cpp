#include "core/layer_stack.hpp"


LayerStack::LayerStack(){
}

LayerStack::~LayerStack(){
    for(auto itr = begin(); itr !=end(); itr++){
        (*itr)->on_detach();
        delete *itr;
    }
}

void LayerStack::push_layer(Layer* layer){
    layers.push_back(layer);
    layer->on_attach();
}

void LayerStack::pop_layer(){
    (*std::prev(layers.end()))->on_detach();
    delete *std::prev(layers.end());
    layers.pop_back();
}