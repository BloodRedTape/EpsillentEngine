#ifndef SCENE_NODE
#define SCENE_NODE

#include <SFML/Graphics.hpp>
#include <list> // basicaly have to be replaced with better data structure
#include <queue>
#include <memory>

class SceneNode{
private:
    std::list<SceneNode*> m_child_nodes;
protected:
    sf::Transform m_transform;
    sf::Transform m_parent_transform;
public:
    SceneNode():
        m_transform()
    {

    }


    //add children in update queue
    // apply parent transfrom to self
    void traverse(std::queue<SceneNode*>& r_queue);
    void add_child(SceneNode*);
    //TODO
    //void remove_child(SceneNode*);
    //yeah i have took it directly from unity XD
    virtual void engine_update();
    virtual void update(const float delta_time)=0;
    virtual void init()=0;
    virtual void start()=0;
    virtual void destroy()=0;

    void translate(const sf::Vector2f& r_offset);
    void translate(const float x_offset,const float y_offset);
    void set_rotation(const float angle);
    //void set_origin();
};

#endif