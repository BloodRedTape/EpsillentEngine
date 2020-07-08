#ifndef COLLIDER_2D_H
#define COLLIDER_2D_H

#include <list>
#include <functional>
#include "config/config.hpp"
#include "core/typedefs.hpp"
#include "core/component.hpp"
#include "SFML/Graphics/Rect.hpp"

class PhysicsEngine;
class Collider2D;

struct Collider2DProperties{
    sf::FloatRect size;
    std::function<void(Collider2D)> callback;
    Collider2DProperties();
};



class ENGINE_API Collider2D: public Component{
private:
    std::list<Collider2D>::iterator m_self;
    sf::FloatRect m_size;
    std::function<void(Collider2D)> m_callback;
private:
    Collider2D(GameObject *owner);
    bool collide(const Collider2D&);
    friend class PhysicsEngine;
public:

    static Collider2D* init(GameObject *);
    void finalize()override;

    void set_properties(const Collider2DProperties&);

    static std::string static_type(){return "Collider2D";}

    static void empty_callback(Collider2D){};
    _ALWAYS_INLINE_ static sf::FloatRect size(float width,float heigth){
        return sf::FloatRect(sf::Vector2f(0,0),sf::Vector2f(width,heigth));
    }
};

#endif