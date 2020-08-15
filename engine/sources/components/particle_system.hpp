#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <memory>
#include "config/config.hpp"
#include "core/component.hpp"
#include "scenes/game_object.hpp"
#include "components/sprite_2d.hpp"
#include "components/transform.hpp"

//do not touch!
struct ParticleSystemProperties{
    //particle data
    sf::Vector2f size;
    float life_time;
    int speed;
    sf::Vector2i dispersion;
    sf::Color color_begin;
    sf::Color color_end;
    float delta_angle;
    // particle system data
    sf::Vector2f spawn_position;
    double spawn_rate;
    ParticleSystemProperties():
        size(40,40),life_time(0.5),speed(100),delta_angle(2),dispersion(50,50),color_begin(sf::Color::White), color_end(sf::Color::Black), spawn_position(0,0), spawn_rate(0.0002)
    {

    }
};

class ENGINE_API Particle: public GameObject{
private:
    sf::Vector2f size;
    float life_time;
    int speed;
    sf::Vector2i dispersion;
    sf::Color color_begin;
    sf::Color color_end;
    float delta_angle;
    float scale;

    Sprite2D* sprite;
    sf::Vector2f direction;
    float angle;
    double time;
public:
    Particle(const sf::Vector2f&,const ParticleSystemProperties&);

    void on_introduce()override;
    void on_update(float dt)override;
};


class ENGINE_API ParticleSystem: public Component{
private:
    std::list<std::unique_ptr<Component>>::iterator m_self;
    ParticleSystemProperties m_properties;
    double time;
public:
    ParticleSystem(GameObject * owner, const ParticleSystemProperties& props = ParticleSystemProperties());
    void update(float dt)override;

    void set_properties(const ParticleSystemProperties&);
    
    ParticleSystemProperties& properties(){return m_properties;};
    
    static ParticleSystem* init(GameObject*, const ParticleSystemProperties& props = ParticleSystemProperties());
    void finalize()override;
    static std::string static_type(){return "ParticleSystem";}
};

#endif