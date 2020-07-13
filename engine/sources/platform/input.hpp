#ifndef INPUT_H
#define INPUT_H

#include "config/config.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"

using KeyCode = sf::Keyboard::Key;
using MouseButton = sf::Mouse::Button;

class Input{
public:
    static sf::Vector2i mouse_position();
    static bool key_pressed(KeyCode);
    static bool mouse_pressed(MouseButton);
};

#endif