#ifndef DEBUG_H
#define DEBUG_H

#include "engine/main/main.hpp" // only for fast debug SHOULD BE REMOVED LATER
#include <assert.h>
#include <string>

#ifdef DEBUG_MODE 

#include <iostream>

class Warning{
    public:
        Warning(const std::string message){
            #ifdef DEBUG_MODE
            std::cout << "[Warrning]: " << message << " !" <<std::endl;
            #endif
        }
};

class Info{
    public:
        Info(const std::string message){
            #ifdef DEBUG_MODE
            std::cout << "[Info]: "<<message << " xD"<<std::endl; 
            #endif
        }

};

#else

#define Info(arg) {}
#define Warning(arg){}


#endif

class Error{
    public:
        Error(const std::string message){
            #ifdef DEBUG_MODE
            std::cout <<"[Error]: " <<message << " !"<<std::endl;
            #else
            //std::cout << "Sorry, your game has been crashed, we will fix it as soon as possible" << std::endl;
            #endif
            std::terminate();
        }
};


#endif