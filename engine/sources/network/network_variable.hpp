#ifndef NETWORK_VARIABLE_H
#define NETWORK_VARIABLE_H

#include "network/network_object.hpp"

template <typename T>
class NetworkVariable{
private:
    T m_value;
    NetworkObject *m_owner;
public:
    explicit NetworkVariable(NetworkObject *owner,const T& value);
    ~NetworkVariable();

    const T& get()const;
    void set(const T& value);
};


template <typename T>
NetworkVariable<T>::NetworkVariable(NetworkObject *owner,const T& value):
    m_value(value), m_owner(owner)
{
    owner->m_net_variables.push_back(NetworkVariableTraits(sizeof(T)),this);
}
template <typename T>
NetworkVariable<T>::~NetworkVariable(){

}

template <typename T>
const T& NetworkVariable<T>::get()const{
    return m_value;
}

template <typename T>
void NetworkVariable<T>::set(const T& value){
    m_value = value;
    // event to notify about variable change
    
}
#endif