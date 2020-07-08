#ifndef COLLIDER_2D_H
#define COLLIDER_2D_H

#include <list>
#include <functional>
#include "config/config.hpp"
#include "core/typedefs.hpp"
#include "core/component.hpp"
#include "SFML/Graphics/Rect.hpp"

class PhysicsEngine;
class Trigger2D;

struct Trigger2DProperties{
    sf::FloatRect size;
    std::function<void(Trigger2D)> callback;
    Trigger2DProperties();
};



class ENGINE_API Trigger2D: public Component{
private:
    std::list<Trigger2D>::iterator m_self;
    sf::FloatRect m_size;
    std::function<void(Trigger2D)> m_callback;
private:
    Trigger2D(GameObject *owner);
    bool collide(const Trigger2D&);
    friend class PhysicsEngine;
public:

    static Trigger2D* init(GameObject *);
    void finalize()override;

    void set_properties(const Trigger2DProperties&);

    static std::string static_type(){return "Trigger2D";}

    static void empty_callback(Trigger2D){};
    _ALWAYS_INLINE_ static sf::FloatRect size(float width,float heigth){
        return sf::FloatRect(sf::Vector2f(0,0),sf::Vector2f(width,heigth));
    }
};

#endif