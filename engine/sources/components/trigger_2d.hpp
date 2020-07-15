#ifndef TRIGGER_2D_H
#define TRIGGER_2D_H

#include <list>
#include <functional>
#include "config/config.hpp"
#include "core/typedefs.hpp"
#include "core/component.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "physics/collider_2d.hpp"

class PhysicsEngine;
class Trigger2D;

struct Trigger2DProperties{
    sf::FloatRect size;
    std::function<void(Trigger2D)> callback;
    Trigger2DProperties();
};

#define CALLBACK(x) std::bind(x,this,std::placeholders::_1)

class ENGINE_API Trigger2D: public Component{
private:
    std::list<Trigger2D>::iterator m_self;
    sf::FloatRect m_size;
    std::function<void(Trigger2D)> m_callback;
private:
    Trigger2D(GameObject *owner, const Trigger2DProperties& props = Trigger2DProperties());
    bool collide(const Trigger2D&);
    bool collide(const Collider2D&);
    friend class PhysicsEngine;
public:

    static Trigger2D* init(GameObject *,const Trigger2DProperties& props = Trigger2DProperties());
    void finalize()override;

    Trigger2D& set_properties(const Trigger2DProperties&);

    static std::string static_type(){return "Trigger2D";}


    _ALWAYS_INLINE_ static sf::FloatRect size(float width,float heigth){
        return sf::FloatRect(sf::Vector2f(0,0),sf::Vector2f(width,heigth));
    }
};

#endif