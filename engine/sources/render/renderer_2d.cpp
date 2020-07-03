#include "utils/debug.hpp"
#include "render/renderer_2d.hpp"
#include "render/draw_call.hpp"
#include "scenes/game_object.hpp"
Renderer2D::Renderer2D()
{
    
}
Renderer2D::~Renderer2D(){

}



void Renderer2D::render(){
    for(Sprite2D& sprite: m_sprites){
        DrawCallInterface::draw(sprite.m_shape,sprite.mp_owner->global_transform());
    }
}


Sprite2D* Renderer2D::sprite_new(GameObject* owner){
    m_sprites.push_back(Sprite2D(owner));
    auto itr = std::prev(m_sprites.end());
    itr->m_self = itr;
    return &*itr;
}

void Renderer2D::sprite_delete(Sprite2D* sprite){
    m_sprites.erase(sprite->m_self);
}