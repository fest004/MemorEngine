#pragma once

#include <iostream>
#include "animation.hpp"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>


class Assets {

public:
  //Methods


void addTexture(const std::string& name, const std::string& path);
void addAnimation(const std::string& name, const std::string& path);
void addAnimation(const std::string &name, const std::string &path, size_t frameCount, size_t speed);
void addSound(const std::string& name, const std::string& path);
void addFont(const std::string& name, const std::string& path);

sf::Texture getTexture(const std::string& name) { return m_Textures[name]; }
Animation getAnimation(const std::string& name) { return m_Animations[name]; };
sf::Sound getSound(const std::string& name) { return m_Sounds[name]; }
sf::Font getFont(const std::string& name) { return m_Fonts[name]; }


private:
  //Variables
  std::map<std::string, sf::Texture> m_Textures;
  std::map<std::string, Animation> m_Animations;
  std::map<std::string, sf::Sound> m_Sounds;
  std::map<std::string, sf::SoundBuffer> m_Buffers;
  std::map<std::string, sf::Font> m_Fonts;
};
