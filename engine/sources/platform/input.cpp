#include "platform/input.hpp"
#include "utils/debug.hpp"
Input * Input::smp_singleton = nullptr;

Input::Input(sf::RenderWindow* win):
    window(win)
{
    if(smp_singleton==nullptr){
        smp_singleton=this;
    }else{
        Warning("Input: created messy object");
    }
}

sf::Vector2i Input::mouse_position(){
    sf::Vector2i pos = sf::Mouse::getPosition(*smp_singleton->window);
    pos.y*=-1;
    return pos;
}
bool Input::key_pressed(KeyCode code){
    return sf::Keyboard::isKeyPressed(code);
}

bool Input::mouse_pressed(MouseButton btn){
    return sf::Mouse::isButtonPressed(btn);
}