#include "engine/scenes/scene.hpp"
#include "engine/core/mainframe.hpp"
BaseScene::BaseScene(){
    Mainframe::get_singleton()->add_processor(RenderEngine::get_singleton()->get_singleton());
    RenderEngine::get_singleton()->set_cluster(&m_render_cluster);
}

BaseScene::~BaseScene(){
    
}