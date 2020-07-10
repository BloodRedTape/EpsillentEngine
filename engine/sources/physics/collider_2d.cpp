#include "physics/collider_2d.hpp"
#include "components/rigidbody_2d.hpp"
#include "scenes/game_object.hpp"
#include <cmath>
#include "unistd.h"


#define abs(x) (x<0?(-1.f*x):x)
//#define abs(x) (x*-1.f)

void Collider2D::collide(Collider2D& collider){
    sf::FloatRect other = collider.m_body->owner()->global_transform().transformRect(collider.m_size);
    sf::FloatRect self = m_body->owner()->global_transform().transformRect(m_size);
    if(self.intersects(other)){
        sf::Vector2f self_mid((2.f*self.left+self.width)/2.f,(2.f*self.top+self.height)/2.f);
        sf::Vector2f other_mid((2.f*other.left+other.width)/2.f,(2.f*other.top+other.height)/2.f);
        sf::Vector2f collision(other_mid.x-self_mid.x,other_mid.y-self_mid.y);
        
        collision.y*=-1.f; // flips 
        float tang = collision.y/collision.x;

        if(collision.x >= 0){
            if(collision.y >= 0){ // I quater
                sf::Vector2f tr(self.left+self.width-self_mid.x,self_mid.y-self.top);
                if(tang > tr.y/tr.x && collider.m_body->force().y <= 0){ // TR
                    collider.m_body->force_add_y(abs(collider.m_body->force().y)*collider.m_body->props().inertia);
                }else if (tang < tr.y/tr.x && collider.m_body->force().x <= 0){
                    collider.m_body->force_add_x(abs(collider.m_body->force().x)*collider.m_body->props().inertia);
                }
            }else{ // IV quater 
                sf::Vector2f dr(self.left+self.width-self_mid.x,self_mid.y-(self.top+self.height));
                if(tang > dr.y/dr.x  && collider.m_body->force().x <= 0){ // DR
                    collider.m_body->force_add_x(abs(collider.m_body->force().x)*collider.m_body->props().inertia);
                }else if(tang < dr.y/dr.x && collider.m_body->force().y >= 0){
                    collider.m_body->force_add_y(abs(collider.m_body->force().y)*-1.f*collider.m_body->props().inertia);
                }
            }
        }else{
            if(collision.y >=0){ // II quater
                sf::Vector2f tl(self.left-self_mid.x,self_mid.y-self.top);
                if(tang > tl.y/tl.x  && collider.m_body->force().x >= 0){ // TL
                    collider.m_body->force_add_x(abs(collider.m_body->force().x)*-1.f*collider.m_body->props().inertia);
                }else if(tang < tl.y/tl.x && collider.m_body->force().y <= 0){
                    collider.m_body->force_add_y(abs(collider.m_body->force().y)*collider.m_body->props().inertia);
                }           
            }else{ // III quater
                sf::Vector2f dl(self.left-self_mid.x,self_mid.y-(self.top+self.height));
                if(tang > dl.y/dl.x && collider.m_body->force().y >= 0){ // DL
                    collider.m_body->force_add_y(abs(collider.m_body->force().y)*-1.f*collider.m_body->props().inertia);
                }else if(tang < dl.y/dl.x  && collider.m_body->force().x >= 0){
                    collider.m_body->force_add_x(abs(collider.m_body->force().x)*-1.f*collider.m_body->props().inertia);
                }    
            }
        }
    }
}