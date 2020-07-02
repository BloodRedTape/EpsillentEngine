#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;


class Component{
protected:
    GameObject * mp_owner;

    void set_owner(GameObject*);
public: 
    Component(){};
    virtual ~Component(){};
};


#endif