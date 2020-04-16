#ifndef COMPONENT_H
#define COMPONENT_H

#include <list> // as always, this should be replaced with better data structure


class Component{
    public:
        typedef std::list<Component*> Cluster;
    protected:
        Cluster& mr_self_cluster;
        Cluster::iterator m_self_iterator;
    public:
        // parametr is a reference to a cluster of the suitable processor
        Component(Cluster&);
        ~Component();
};
typedef Component::Cluster Cluster;


#endif