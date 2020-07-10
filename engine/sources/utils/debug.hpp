#ifndef DEBUG_H
#define DEBUG_H

#include "config/config.hpp" // only for fast debug SHOULD BE REMOVED LATER
#include <assert.h>
#include <string>
#include <iostream>

#ifdef PROFILING_MODE

class Profiling{
public:
    Profiling(const std::string& message){
        std::cout<<"[Profiler]: " << message << std::endl;
    }
};


#else
    #define Profiling(x) {}
#endif

#define ARG(x) std::to_string(x)
#define ARG_VEC(n,v) std::string(n)+std::string(" x: ") + std::to_string(v.x) + std::string(" y:") + std::to_string(v.y) + std::string(" ") 

#ifdef DEBUG_MODE 

#define ASSERT(exp) ASSERT_ERROR(exp, "Asserion failed")
#define ASSERT_ERROR(exp,msg) if(!(exp)){Error(msg);}
#define ASSERT_WARRNING(exp,msg) if(!(exp)){Warning(msg);}
#define ASSERT_INFO(exp,msg) if(!(exp)){Info(msg);}



class ENGINE_API Warning{
    public:
        Warning(const std::string message){
            #ifdef DEBUG_MODE
            std::cout << "[Warrning]: " << message << " !" <<std::endl;
            #endif
        }
};

class ENGINE_API Info{
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
#define ASSERT(exp) {}
#define ASSERT_ERROR(exp,msg) {}
#define ASSERT_WARRNING(exp,msg) {}
#define ASSERT_INFO(exp,msg) {} 
#endif

class ENGINE_API Error{
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