#include "core/mainframe.hpp"
#include "utils/debug.hpp"

Mainframe* Mainframe::smp_singleton = nullptr;


Mainframe::Mainframe(){
    if(smp_singleton==nullptr){
        smp_singleton=this;
        Info("Mainframe: created");
    }else{
        Warning("Mainframe: created messy object");
    }
}

Mainframe::~Mainframe(){
    Info("Mainframe: deleted");
}

void Mainframe::add_processor(Processor* p_processor){
    get_singleton()->m_processors.push_back(p_processor);
    Info("Mainframe: added a processor");
}

void Mainframe::reload(){
    get_singleton()->m_processors.clear();
    Info("Mainframe: reloaded");
    Info("Mainframe: time to add new processors!");
}

void Mainframe::compute(){
    for(std::vector<Processor*>::iterator itr = get_singleton()->m_processors.begin(); itr!=get_singleton()->m_processors.end(); itr++){
        
    }
}