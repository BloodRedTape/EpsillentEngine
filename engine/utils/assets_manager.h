#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class AssetsManager{
    public:
        static sf::Texture* get_texture(const char* filename);
        static sf::Font* get_font(std::string const& filename);
        AssetsManager()=delete;
        AssetsManager(const AssetsManager&) = delete;
    private:
        static std::map<std::string, sf::Texture> sm_textures;
        static std::map<std::string, sf::Font> sm_fonts;
};


#endif