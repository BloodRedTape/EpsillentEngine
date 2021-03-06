#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "config/config.hpp"

class ENGINE_API AssetsManager{

    private:
        static std::unordered_map<std::string, sf::Texture> sm_textures;
        static std::unordered_map<std::string, sf::Font> sm_fonts;
    public:
        AssetsManager()=delete;
        AssetsManager(const AssetsManager&) = delete;
        static sf::Texture &get_texture(const char* filename);
        static sf::Font &get_font(const char* filename);
        static void clear();

};


#endif