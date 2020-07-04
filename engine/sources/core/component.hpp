#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;


class Component{
protected:
    GameObject * mp_owner;
public: 
    Component(GameObject*);
    virtual ~Component(){};
    virtual void finalize()=0;
    virtual void update(float dt){};
};


#endif