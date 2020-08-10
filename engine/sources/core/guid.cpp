#include "core/guid.hpp"
#include "core/math/random.hpp"

GUID::GUID(){
    for(unsigned char &c: guid){
        c = Random::integer(0,256);
    }
}

bool GUID::operator==(const GUID &other) const{
    return guid == other.guid;
}
bool GUID::operator!=(const GUID &other) const{
    return guid != other.guid;
}

GUID::operator std::string()const{
    return std::string(
        std::to_string(*(uint32*)(&guid[0])) + "-" +
        std::to_string(*(uint16*)(&guid[4])) + "-" +
        std::to_string(*(uint16*)(&guid[8])) + "-" +
        std::to_string(*(uint32*)(&guid[12]))
    );
}

const std::array<unsigned char, 16>& GUID::bytes() const{
    return guid;
}

void GUID::clear(){
    std::fill(guid.begin(),guid.end(),0);
}
