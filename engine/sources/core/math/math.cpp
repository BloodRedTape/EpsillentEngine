#include "core/math/math.hpp"

namespace Math{


double vector_angle(const sf::Vector2f& vec){
    if(vec.x>=0 && vec.y >=0){
        return 360.f-1.f*atan(vec.y/vec.x)/M_PI*180;
    }else if(vec.y>= 0 && vec.x<0){
        return -1.f*atan(vec.y/vec.x)/M_PI*180.f+180;
    }else if(vec.x >= 0&& vec.y <0){
        return 360.f-1.f*(360.f+atan(vec.y/vec.x)/M_PI*180.f);
    }else{
        return 360.f-1.f*(180.f+atan(vec.y/vec.x)/M_PI*180.f);
    }

}

}; // end of Math::