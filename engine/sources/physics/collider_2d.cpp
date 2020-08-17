#include "physics/collider_2d.hpp"
#include "components/rigidbody_2d.hpp"
#include "scenes/game_object.hpp"
#include "core/math/math.hpp"


void Collider2D::collide(Collider2D& collider){
    sf::FloatRect other = collider.m_body->owner()->global_transform().transformRect(collider.m_size);
    sf::FloatRect self = m_body->owner()->global_transform().transformRect(m_size);
    if(self.intersects(other)){
        sf::Vector2f self_mid((2.f*self.left+self.width)/2.f,(2.f*self.top+self.height)/2.f);
        sf::Vector2f other_mid((2.f*other.left+other.width)/2.f,(2.f*other.top+other.height)/2.f);
        float collision = Math::degree(Math::unsigned_angle(sf::Vector2f(other_mid.x-self_mid.x,other_mid.y-self_mid.y)));
        float dl = Math::degree(Math::unsigned_angle(sf::Vector2f(self.left-self_mid.x,self_mid.y-(self.top+self.height))));
        float tl = Math::degree(Math::unsigned_angle(sf::Vector2f(self.left-self_mid.x,self_mid.y-self.top)));
        float tr = Math::degree(Math::unsigned_angle(sf::Vector2f(self.left+self.width-self_mid.x,self_mid.y-self.top)));
        float dr = Math::degree(Math::unsigned_angle(sf::Vector2f(self.left+self.width-self_mid.x,self_mid.y-(self.top+self.height))));

        if(collision >= tr && collision <tl){
            if(collider.m_body->force().y<= 0)
                collider.m_body->force_add_y(abs(collider.m_body->force().y)*collider.m_body->props().rebound);
            if(collider.m_body->translation().y<= 0)
                collider.m_body->move_y(abs(collider.m_body->translation().y));
        }else if(collision >= tl && collision < dl){
            if(collider.m_body->force().x>= 0)
                collider.m_body->force_add_x(abs(collider.m_body->force().x)*-1.f*collider.m_body->props().rebound);
            if(collider.m_body->translation().x>= 0)
                collider.m_body->move_x(abs(collider.m_body->translation().x)*-1.f);
        }else if(collision >= dl && collision < dr){
            if(collider.m_body->force().y>= 0)
                collider.m_body->force_add_y(abs(collider.m_body->force().y)*-1.f*collider.m_body->props().rebound);
            if(collider.m_body->translation().y>= 0)
                collider.m_body->move_y(abs(collider.m_body->translation().y)*-1.f);
        }else{
            if(collider.m_body->force().x<= 0)
                collider.m_body->force_add_x(abs(collider.m_body->force().x)*collider.m_body->props().rebound);
            if(collider.m_body->translation().x<= 0)
                collider.m_body->move_x(abs(collider.m_body->translation().x));
        }
    }
}