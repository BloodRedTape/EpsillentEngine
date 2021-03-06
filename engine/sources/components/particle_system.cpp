#include "components/particle_system.hpp"
#include "components/sprite_2d.hpp"
#include "scenes/game_object.hpp"
#include "scenes/scene.hpp"
#include <cstring>
#include "core/math/math.hpp"

Particle::Particle(const sf::Vector2f& position,const ParticleSystemProperties& prop):
    time(0.0f),
    direction(Random::integer(-prop.speed+1,prop.speed),Random::integer(-prop.speed+1,prop.speed))
{
    translate(position);
    memcpy(&size.x,&prop.size.x,sizeof(prop)-16);
}


void Particle::on_introduce(){
    set_tag("Engine::Particle");
    sprite = component_add<Sprite2D>();
    sprite->set_color(color_begin);
    //sprite->set_color(sf::Color(color_begin.r - (color_begin.r-color_end.r)*(1-scale),color_begin.g - (color_begin.g-color_end.g)*(1-scale),color_begin.b - (color_begin.b-color_end.b)*(1-scale),color_begin.a - (color_begin.a-color_end.a)*(1-scale)));
    sprite->set_size(size);
    translate(Random::integer(-dispersion.x/2,dispersion.x/2),Random::integer(-dispersion.y/2,dispersion.y/2));
}

void Particle::on_update(float dt){
    time+=dt;
    if(time>=life_time)destroy();
    scale = (life_time-time)/life_time;
    sprite->set_size(size*scale);
    sprite->set_color(sf::Color(color_begin.r - (color_begin.r-color_end.r)*(1-scale),color_begin.g - (color_begin.g-color_end.g)*(1-scale),color_begin.b - (color_begin.b-color_end.b)*(1-scale),color_begin.a - (color_begin.a-color_end.a)*(1-scale)));
    translate(direction*dt);
    rotate(delta_angle*dt);
}



ParticleSystem::ParticleSystem(GameObject * owner, const ParticleSystemProperties& props):
    Component(owner),
    m_properties(props),
    time(0)
{

}

void ParticleSystem::set_properties(const ParticleSystemProperties& props){
    m_properties = props;
}

void ParticleSystem::update(float dt){
    time +=dt;
    while(time>=m_properties.spawn_rate){
        time-=m_properties.spawn_rate;
        mp_owner->scene()->object_introduce(new Particle(mp_owner->global_position()+m_properties.spawn_position,m_properties));
    }
}


ParticleSystem* ParticleSystem::init(GameObject* owner, const ParticleSystemProperties& props){
    ParticleSystem *p = new ParticleSystem(owner, props);
    owner->scene()->cluster().components.emplace_back(p);
    p->m_self = std::prev(owner->scene()->cluster().components.end());
    return p;
}

void ParticleSystem::finalize(){
    mp_owner->scene()->cluster().components.erase(m_self);
}
