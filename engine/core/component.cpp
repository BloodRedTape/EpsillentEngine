#include "engine/core/component.hpp"


Component::Component(Cluster& r_cluster):
mr_self_cluster(r_cluster)
{
    mr_self_cluster.push_back(this);
    //i hope it will pass to the correct list node
    m_self_iterator=mr_self_cluster.end();
}


Component::~Component(){
    mr_self_cluster.erase(m_self_iterator);
}