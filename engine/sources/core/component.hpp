#ifndef COMPONENT_H
#define COMPONENT_H

#include "config/config.hpp"
class GameObject;


class ENGINE_API Component{
protected:
    GameObject * mp_owner;
public: 
    Component(GameObject*);
    
    GameObject* owner()const;

    virtual ~Component(){};
    virtual void finalize()=0;
    virtual void update(float dt){};
};


#endif