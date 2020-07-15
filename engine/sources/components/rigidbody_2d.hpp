#ifndef RIGIDBODY_2D_H
#define RIGIDBODY_2D_H

#include "config/config.hpp"
#include "core/component.hpp"
#include "SFML/System/Vector2.hpp"
#include "physics/collider_2d.hpp"
#include <string>
#include <vector>

class PhysicsEngine;
struct Rigidbody2DProperties{
    sf::Vector2f gravity;
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

    friend class PhysicsEngine;
public:
    Rigidbody2D(GameObject *owner,const Rigidbody2DProperties& props = Rigidbody2DProperties());
    Rigidbody2D& set_properties(const Rigidbody2DProperties&);
    void force_add(const sf::Vector2f&);
    void force_add_x(float f){force_add(sf::Vector2f(f,0));};
    void force_add_y(float f){force_add(sf::Vector2f(0,f));};
    void bounce();
    void collider_add(const sf::Vector2f& size, const sf::Vector2f& position = sf::Vector2f(0,0));

    sf::Vector2f force()const{return m_force;}
    const Rigidbody2DProperties& props()const{return m_props;}

    static Rigidbody2D *init(GameObject*, const Rigidbody2DProperties& props  = Rigidbody2DProperties());
    void finalize()override;

    static std::string static_type(){return "Rigidbody2D";}
};
#endif