#ifndef RANDOM_H
#define RANDOM_H


#include "config/config.hpp"

class ENGINE_API Random{
public:
    static void seed(int);
    static int integer(int first,int last);
};

#endif