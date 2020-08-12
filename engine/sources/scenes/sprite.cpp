#include "render/renderer_2d.hpp"
#include "render/draw_call.hpp"
#include "sprite.hpp"


void Sprite::update(){
    //physics update done here !
}

void Sprite::render(){
    DrawCallInterface::draw(m_shape, global_transform());
}

void Sprite::on_destroy(){

}
void Sprite::on_start(){

}
void Sprite::on_update(const float dt){

}