#ifndef COLLIDER_2D_H
#define COLLIDER_2D_H

#include <list>
#include "config/config.hpp"
#include "core/component.hpp"
#include "SFML/Graphics/Rect.hpp"


class Rigidbody2D;
class PhysicsEngine;

class ENGINE_API Collider2D{
private:
    Rigidbody2D * m_body;
    std::list<Collider2D>::iterator m_self;
    sf::FloatRect m_size;
    friend class Rigidbody2D;
    friend class PhysicsEngine;
public:

    void collide(Collider2D&);

    sf::FloatRect size()const{return m_size;}
    Rigidbody2D *body()const{return m_body;}
};

#endif