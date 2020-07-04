#ifndef RENDER_H
#define RENDER_H

#include <list>
#include <memory>
#include "config/config.hpp"
#include <SFML/Graphics.hpp>
#include "components/sprite_2d.hpp"

class ENGINE_API Renderer2D{
private:
    std::list<Sprite2D> m_sprites;
public:
    Renderer2D(const Renderer2D&)=delete;
    Renderer2D& operator=(const Renderer2D&)=delete;


    Renderer2D();
    ~Renderer2D();

    void render();

    Sprite2D* sprite_new(GameObject*);
    void sprite_delete(Sprite2D*);

};




#endif