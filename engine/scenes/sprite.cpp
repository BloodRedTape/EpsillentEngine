#include "engine/render/render_engine.hpp"
#include "sprite.hpp"


void Sprite::engine_update(){
    //physics update done here !
    RenderEngine::get_singleton()->render(m_shape, m_parent_transform*m_transform);
}

void Sprite::init(){

}
void Sprite::destroy(){

}
void Sprite::start(){

}
void Sprite::update(const float dt){

}