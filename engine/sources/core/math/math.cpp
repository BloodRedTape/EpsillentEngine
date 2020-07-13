#include "core/math/math.hpp"

namespace Math{


double vector_angle(const sf::Vector2f& vec){
    return atan(vec.y/vec.x)/M_PI*180;
}

};