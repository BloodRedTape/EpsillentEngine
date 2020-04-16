#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <vector>
#include "engine/core/processor.hpp"


class Mainframe{
    private:
        static Mainframe* smp_singleton;
        std::vector<Processor*> m_processors;

    public:
        Mainframe();
        ~Mainframe();
        static Mainframe* get_singleton(){return smp_singleton;}
        void add_processor(Processor*);
        void reload();
        void compute();
};


#endif