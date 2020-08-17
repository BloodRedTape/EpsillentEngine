#ifndef RIGIDBODY_2D_H
#define RIGIDBODY_2D_H

#include "config/config.hpp"
#include "core/component.hpp"
#include "SFML/System/Vector2.hpp"
#include "physics/collider_2d.hpp"
#include <string>
#include <vector>
#include "core/typedefs.hpp"

class PhysicsEngine;
struct Rigidbody2DProperties{
    float gravity;
    float mass;
    float inertia;
    float rebound;
    Rigidbody2DProperties();
};

class ENGINE_API Rigidbody2D: public Component{
private:
    std::list<Rigidbody2D>::iterator m_self;
    std::vector<Collider2D*> m_colliders;
    Rigidbody2DProperties m_props;
    sf::Vector2f m_force;
    sf::Vector2f m_translation;

    friend class PhysicsEngine;
public:
    Rigidbody2D(GameObject *owner,const Rigidbody2DProperties& props = Rigidbody2DProperties());
    Rigidbody2D& set_properties(const Rigidbody2DProperties&);
    void force_add(const sf::Vector2f&);
    _ALWAYS_INLINE_ void force_add_x(float f){force_add(sf::Vector2f(f,0));};
    _ALWAYS_INLINE_ void force_add_y(float f){force_add(sf::Vector2f(0,f));};
    void move(const sf::Vector2f &offset);
    _ALWAYS_INLINE_ void move_x(float f){move(sf::Vector2f(f,0));};
    _ALWAYS_INLINE_ void move_y(float f){move(sf::Vector2f(0,f));};
    void bounce();
    void collider_add(const sf::Vector2f& size, const sf::Vector2f& position = sf::Vector2f(0,0));

    sf::Vector2f force()const{return m_force;}
    sf::Vector2f translation()const{return m_translation;}
    const Rigidbody2DProperties& props()const{return m_props;}

    static Rigidbody2D *init(GameObject*, const Rigidbody2DProperties& props  = Rigidbody2DProperties());
    void finalize()override;

    static std::string static_type(){return "Rigidbody2D";}
};
#endif