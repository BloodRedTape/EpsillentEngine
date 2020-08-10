#include "core/guid.hpp"
#include "core/math/random.hpp"

GUID::GUID(){
    for(unsigned char &c: guid){
        c = Random::integer(1,256);
    }
}

bool GUID::operator==(const GUID &other) const{
    return guid == other.guid;
}
bool GUID::operator!=(const GUID &other) const{
    return guid != other.guid;
}


const std::array<unsigned char, 16>& GUID::bytes() const{
    return guid;
}

void GUID::clear(){
    std::fill(guid.begin(),guid.end(),0);
}

bool GUID::is_valid()const{
    return guid[0];
}