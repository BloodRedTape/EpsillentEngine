#ifndef INSTANCE_H
#define INSTANCE_H
#include <mutex>
#include "config/config.hpp"
typedef uint32_t InstanceID;

// Used just to get an unique ID for instance
// CONTRARY TO COMMON BELIFES IT
// IS NOT SUPPOSED TO STORE ALL INSTANCES POINTERS
class ENGINE_API InstanceDB{
    private:
        static std::mutex seed_mutex;  
        static InstanceID s_seed;
        InstanceDB()=delete;
    public:
        static InstanceID assign_id();
        
};


#endif