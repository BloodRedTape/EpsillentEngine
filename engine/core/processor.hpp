#ifndef PROCESSOR_H
#define PROCESSOR_H


#include "engine/core/component.hpp"



// NO, STOP THINKING ABOUT IT
// THERE IS NOTHING CONNECTED WITH CPU
// also it would be nice if your inheritance from this class was a singleton
//template<typename T> // this template is just for fun XD
class Processor{
    protected:
        Cluster* p_current_cluster;
    public:
        Processor(Cluster*);
        void set_cluster();
        virtual void process()=0;

};




#endif