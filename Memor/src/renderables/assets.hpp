#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "animation.hpp"


class Assets {

public:
  //Methods

void loadFromFile(const std::string& path);

void AddTexture(const std::string& name, const std::string& path);
void addAnimation(const std::string& name, const std::string& path);
void addSound(const std::string& name, const std::string& path);
void addFont(const std::string& name, const std::string& path);

sf::Texture getTexture(const std::string& name) { return m_Textures[name]; }
Animation getAnimation(const std::string& name) { return m_Animations[name]; };
sf::Sound getSound(const std::string& name) { return m_Sounds[name]; }
sf::Font getFont(const std::string& name) { return m_Fonts[name]; }


private:
  //Variables
  std::unordered_map<std::string, sf::Texture> m_Textures;
  std::unordered_map<std::string, Animation> m_Animations;
  std::unordered_map<std::string, sf::Sound> m_Sounds;
  std::unordered_map<std::string, sf::Font> m_Fonts;
};
