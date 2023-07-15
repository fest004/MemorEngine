#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>


class Assets {

public:
  //Methods

sf::Texture getTexture(std::string path);
Animation getAnimation(std::string path);
sf::Sound getSound(std::string path);
sf::Font getFont(std::string path);


private:
  //Variables
  std::unordered_map<std::string, sf::Texture> m_Textures;
  std::unordered_map<std::string, Animations> m_Animations;
  std::unordered_map<std::string, sf::Sound> m_Sounds;
  std::unordered_map<std::string, sf::Font> m_Fonts;
};
