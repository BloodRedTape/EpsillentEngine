#include "platform/input.hpp"

sf::Vector2i Input::mouse_position(){
    return sf::Mouse::getPosition();
}
bool Input::key_pressed(KeyCode code){
    return sf::Keyboard::isKeyPressed(code);
}

bool Input::mouse_pressed(MouseButton btn){
    return sf::Mouse::isButtonPressed(btn);
}