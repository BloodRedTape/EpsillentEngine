#ifndef MATH_H
#define MATH_H
#include "SFML/System/Vector2.hpp"
#include "core/math/random.hpp"
#include "core/typedefs.hpp"
#define PI 3.141
#include <cmath>

#define abs(x) ((x)>0?(x):(x)*-1)

namespace Math{

double vector_angle(const sf::Vector2f&);

_FORCE_INLINE_ sf::Vector2f points_to_vector(const sf::Vector2f& begin,const sf::Vector2f& end){
    return sf::Vector2f(end.x-begin.x, end.y-begin.y);
}

_FORCE_INLINE_ sf::Vector2f normalize(const sf::Vector2f& vector){
    sf::Vector2f absolute(abs(vector.x),abs(vector.y));
    if(absolute.x==0.0f)
        absolute.x=0.0001f;
    if(absolute.y==0.0f)
        absolute.y=0.0001f;
    if(absolute.x>=absolute.y){
        return sf::Vector2f(absolute.x/absolute.x*(vector.x/absolute.x),absolute.y/absolute.x*(vector.y/absolute.y));
    }else{
        return sf::Vector2f(absolute.x/absolute.y*(vector.x/absolute.x),absolute.y/absolute.y*(vector.y/absolute.y));
    }
}

_FORCE_INLINE_ float degree(float rad){
    return rad/PI*180;
}

_FORCE_INLINE_ float rad(float degree){
    return degree/180*PI;
}

}; // end of Math::
#endif