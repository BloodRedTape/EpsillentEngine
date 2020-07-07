#include "components/particle_system.hpp"
#include "components/sprite_2d.hpp"
#include "scenes/game_object.hpp"
#include "scenes/scene.hpp"
#include <cstring>

Particle::Particle(const sf::Transform& trans,const ParticleSystemProperties& prop):
    time(0.0f),
    direction(rand()%(prop.speed*2)-prop.speed,rand()%(2*prop.speed)-prop.speed)
{
    set_transform(trans);
    memcpy(&size.x,&prop.size.x,sizeof(prop)-16);
}


void Particle::on_init(){
    sprite = component_add<Sprite2D>("Sprite");
    sprite->set_color(sf::Color(color_begin.r + (color_begin.r-color_end.r)*(1-scale),color_begin.g + (color_begin.g-color_end.g)*(1-scale),color_begin.b + (color_begin.b-color_end.b)*(1-scale),255));
    sprite->set_size(size);
    translate(rand()%dispersion.x-dispersion.x/2,rand()%dispersion.y-dispersion.y/2);
}

void Particle::on_update(float dt){
    time+=dt;
    if(time>=life_time)destroy();
    scale = (life_time-time)/life_time;
    sprite->set_size(size*scale);
    sprite->set_color(sf::Color(color_begin.r - (color_begin.r-color_end.r)*(1-scale),color_begin.g - (color_begin.g-color_end.g)*(1-scale),color_begin.b - (color_begin.b-color_end.b)*(1-scale),255));
    translate(direction*dt);
    rotate(delta_angle*dt);
}



ParticleSystem::ParticleSystem(GameObject * owner):
    Component(owner),
    m_properties(),
    time(0)
{

}

void ParticleSystem::set_properties(const ParticleSystemProperties& props){
    m_properties = props;
}

void ParticleSystem::update(float dt){
    time +=dt;
    if(time>=m_properties.spawn_rate){
        time-=m_properties.spawn_rate;
        mp_owner->scene()->object_introduce(new Particle(mp_owner->global_transform().translate(m_properties.spawn_position),m_properties));
    }
}


ParticleSystem* ParticleSystem::init(GameObject* owner){
    ParticleSystem *p = new ParticleSystem(owner);
    owner->scene()->cluster().components.push_back(p);
    p->m_self = std::prev(owner->scene()->cluster().components.end());
    return p;
}

void ParticleSystem::finalize(){
    mp_owner->scene()->cluster().components.erase(m_self);
}
