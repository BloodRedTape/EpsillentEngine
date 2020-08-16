#include "core/math/math.hpp"

namespace Math{


float angle(const sf::Vector2f& vec){
    return atan2f(vec.y,vec.x);
}

float unsigned_angle(const sf::Vector2f& vec){
    float angle = atan2f(vec.y,vec.x);
    return angle < 0 ? 2*PI + angle : angle;
}

}; // end of Math::