#ifndef MATH_H
#define MATH_H
#include "SFML/System/Vector2.hpp"
#include "core/math/random.hpp"
#include "core/typedefs.hpp"
#define PI 3.14159265358979323846
#include <cmath>

#define abs(x) ((x)>0?(x):(x)*-1)

namespace Math{
//in radians
float angle(const sf::Vector2f&);
//in radians
float unsigned_angle(const sf::Vector2f&);

_FORCE_INLINE_ sf::Vector2f points_to_vector(const sf::Vector2f& begin,const sf::Vector2f& end){
    return sf::Vector2f(end.x-begin.x, end.y-begin.y);
}
template <typename T>
_FORCE_INLINE_ sf::Vector2<T> normalize(const sf::Vector2<T>& vector){
    T length = std::sqrt(vector.x*vector.x+vector.y*vector.y); 
    return sf::Vector2<T>(vector.x/length,vector.y/length);
}

_FORCE_INLINE_ float degree(float rad){
    return rad/PI*180;
}

_FORCE_INLINE_ float rad(float degree){
    return degree/180*PI;
}

_FORCE_INLINE_ float length(const sf::Vector2f &vector){
    return sqrtf(vector.x*vector.x+vector.y*vector.y);
}

}; // end of Math::
#endif