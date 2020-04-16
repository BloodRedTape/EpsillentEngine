#include "test.hpp"


TestComponent::TestComponent(Cluster& cluster):
    Component(cluster)
{
i=0;
}


void Scene::init(){
    
    TestComponent*n = new TestComponent(test_cluster);
    TestProcessor *p = new TestProcessor(&test_cluster);
    Mainframe::get_singleton()->add_processor(p);
    
}

void Scene::start(){

}
void Scene::destroy(){

}