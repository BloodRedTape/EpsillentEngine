#ifndef MATH_H
#define MATH_H
#include "SFML/System/Vector2.hpp"
#include "core/math/random.hpp"
#include "core/typedefs.hpp"
#include <cmath>
namespace Math{

double vector_angle(const sf::Vector2f&);

_ALWAYS_INLINE_ sf::Vector2f points_to_vector(const sf::Vector2f& begin,const sf::Vector2f& end){
    return sf::Vector2f(end.x-begin.x, end.y-begin.y);
}


}; // end of Math::
#endif