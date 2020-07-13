#include "core/math/random.hpp"
#include <cstdlib>

#define abs(x) (x<0?(-1.f*x):x)


void Random::seed(int seed){
    srand(seed);
}

int Random::integer(int first,int last){
    return rand()%(last-first)+first;
}

