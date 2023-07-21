#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "animation.hpp"


class Assets {

public:
  //Methods

sf::Texture getTexture(std::string path) { return m_Textures[path]; }
Animation getAnimation(std::string path);
sf::Sound getSound(std::string path) { return m_Sounds[path]; }
sf::Font getFont(std::string path) { return m_Fonts[path]; }


private:
  //Variables
  std::unordered_map<std::string, sf::Texture> m_Textures;
  std::unordered_map<std::string, Animation> m_Animations;
  std::unordered_map<std::string, sf::Sound> m_Sounds;
  std::unordered_map<std::string, sf::Font> m_Fonts;
};
