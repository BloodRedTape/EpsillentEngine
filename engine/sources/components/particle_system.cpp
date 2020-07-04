#include "components/particle_system.hpp"
#include "components/sprite_2d.hpp"
#include "scenes/game_object.hpp"
#include "scenes/scene.hpp"

Particle::Particle(const sf::Transform& trans,const ParticleProperties& prop):
    props(prop),
    time(0.0f),
    direction(rand()%(props.speed*2)-props.speed,rand()%(2*props.speed)-props.speed)
{
    set_transform(trans);
}


void Particle::on_init(){
    sprite = component_add<Sprite2D>("Sprite");
    sprite->set_color(sf::Color(props.color_begin.r + (props.color_begin.r-props.color_end.r)*(1-props.scale),props.color_begin.g + (props.color_begin.g-props.color_end.g)*(1-props.scale),props.color_begin.b + (props.color_begin.b-props.color_end.b)*(1-props.scale),255));
    sprite->set_size(props.size);
    translate(rand()%props.dispersion.x-props.dispersion.x/2,rand()%props.dispersion.y-props.dispersion.y/2);
}

void Particle::on_update(float dt){
    time+=dt;
    if(time>=props.life_time)destroy();
    props.scale = (props.life_time-time)/props.life_time;
    sprite->set_size(props.size*props.scale);
    sprite->set_color(sf::Color(props.color_begin.r - (props.color_begin.r-props.color_end.r)*(1-props.scale),props.color_begin.g - (props.color_begin.g-props.color_end.g)*(1-props.scale),props.color_begin.b - (props.color_begin.b-props.color_end.b)*(1-props.scale),255));
    translate(direction*dt);
}



ParticleSystem::ParticleSystem(GameObject * owner):
    Component(owner),
    spawn_props(sf::Vector2f(40,40),sf::Vector2i(50,50),1.f,400,sf::Color::White,sf::Color::White),
    spawn_rate(0.01f),
    spawn_position(0,0),
    time(0)
{

}

void ParticleSystem::set_properties(const ParticleProperties& props,double rate, const sf::Vector2f& pos){
    if(rate < 0.0)
        rate = 0.000001;
    spawn_props= props;
    spawn_rate = rate;
    spawn_position = pos;
}

void ParticleSystem::update(float dt){
    time +=dt;
    if(time>=spawn_rate){
        time-=spawn_rate;
        mp_owner->scene()->object_introduce(new Particle(mp_owner->global_transform().translate(spawn_position),spawn_props));
    }
}


ParticleSystem* ParticleSystem::init(GameObject* owner){
    ParticleSystem *p = new ParticleSystem(owner);
    owner->scene()->components().push_back(p);
    p->m_self = std::prev(owner->scene()->components().end());
    return p;
}

void ParticleSystem::finalize(){
    mp_owner->scene()->components().erase(m_self);
}
