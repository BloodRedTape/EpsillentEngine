#ifndef TEST_H
#define TEST_H

#include "engine/core/component.hpp"
#include "engine/scenes/scene.hpp"
#include "engine/render/render_engine.hpp"
#include "engine/core/processor.hpp"
#include "engine/core/mainframe.hpp"

#include <iostream>

class TestComponent: public Component{
    int i;
    public:
        TestComponent(Cluster&);

        void doing(){
            i++;
            
        }

};

class TestProcessor: public Processor{
    public:
        TestProcessor(Cluster* clust):
            Processor(clust)
        {

        }
        void process(){
            for(Cluster::iterator itr = p_current_cluster->begin(); itr!=p_current_cluster->end(); itr++){
                static_cast<TestComponent*>(*itr)->doing();
            }
        }
};

class Scene:public BaseScene{
    protected:
        sf::CircleShape cs{800};
        Cluster test_cluster;
        sf::RectangleShape rs{sf::Vector2f(20,40)};
        
    public:
        
    Scene(){
        cs.setFillColor(sf::Color::Green);
        rs.setFillColor(sf::Color::Red);
        
        r.push_back(&cs);
        r.push_back(&rs);
    }
    void start()override;
    void init()override;
     void destroy()override;


};









#endif