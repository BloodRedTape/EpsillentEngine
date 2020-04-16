#include <mutex>
#include "engine/core/instance.hpp"


std::mutex InstanceDB::seed_mutex; 
InstanceID InstanceDB::s_seed=1;

InstanceID InstanceDB::assign_id(){
    std::lock_guard<std::mutex>guard (seed_mutex);
    return s_seed++;
}