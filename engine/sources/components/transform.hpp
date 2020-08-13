#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "config/config.hpp"
#include <string>
#include "core/component.hpp"
#include "SFML/Graphics/Transform.hpp"

class ENGINE_API Transform: public Component{
private:
    sf::Vector2f m_local_position;
    sf::Vector2f m_global_position;
    float rotation;
    bool m_dirty;

    friend class GameObject;
public:
    Transform(GameObject* owner);

    static std::string static_type(){return "Transform";}
    void finalize()override{};

    void translate(const sf::Vector2f& r_offset);
    void translate(const float x_offset,const float y_offset);
    void rotate(const float angle);

    sf::Vector2f global_position();
    const sf::Vector2f& local_position();

    void set_local_position(const sf::Vector2f &position);

    sf::Transform global_transform();
    const sf::Transform& local_transform();
};


#endif