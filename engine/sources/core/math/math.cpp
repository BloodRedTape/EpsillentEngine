#include "core/math/math.hpp"

namespace Math{


float angle(const sf::Vector2f& vec){
    return Math::degree(atan2f(vec.y,vec.x));
}

float unsigned_angle(const sf::Vector2f& vec){
    float angle = Math::degree(atan2f(vec.y,vec.x));
    return angle < 0 ? 360 + angle : angle;
}

}; // end of Math::