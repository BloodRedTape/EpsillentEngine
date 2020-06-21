#include "engine/render/render_engine.hpp"
#include "sprite.hpp"


void Sprite::update(){
    //physics update done here !
}

void Sprite::render(){
    RenderEngine::get_singleton()->render(m_shape, global_transform());

}

void Sprite::on_init(){

}
void Sprite::on_destroy(){

}
void Sprite::on_start(){

}
void Sprite::on_update(const float dt){

}