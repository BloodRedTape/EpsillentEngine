#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "core/component.hpp"
#include "scenes/game_object.hpp"
#include "components/sprite_2d.hpp"
#include "components/transform.hpp"

struct ParticleProperties{
    sf::Vector2f size;
    float life_time;
    int speed;
    sf::Vector2i dispersion;
    sf::Color color_begin;
    sf::Color color_end;
    float scale;
    ParticleProperties(const sf::Vector2f& dim,const sf::Vector2i& disp, float time, int sp,const sf::Color& begin, const sf::Color& end):
        size(dim), dispersion(disp) , life_time(time),speed(sp), color_begin(begin), color_end(end), scale(1)
    {
    }
};

class Particle: public GameObject{
private:
    Sprite2D* sprite;
    ParticleProperties props;
    sf::Vector2f direction;
    double time;
public:
    Particle(const sf::Transform&,const ParticleProperties&);

    void on_init()override;
    void on_update(float dt)override;
};


class ParticleSystem: public Component{
private:
    std::list<Component*>::iterator m_self;
    ParticleProperties spawn_props;
    sf::Vector2f spawn_position;
    double time;
    double spawn_rate;
public:
    ParticleSystem(GameObject * owner);
    void update(float dt)override;

    void set_properties(const ParticleProperties&, double spawn_rate, const sf::Vector2f& spawn_pos = sf::Vector2f(0,0));

    static ParticleSystem* init(GameObject*);
    void finalize()override;
    static std::string static_type(){return "ParticleSystem";}
};

#endif