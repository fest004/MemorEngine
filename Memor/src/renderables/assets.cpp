#include "assets.hpp"
#include "animation.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Texture.hpp>


void Assets::loadFromFile(const std::string& path)
{
  std::cout << "LoadFromFile" << std::endl;
  // TODO Load assets lmao

  addAnimation("Question1", "temp/A3/assets/question1.png");
  addAnimation("Brick", "temp/A3/assets/brick.png");
  addAnimation("Shoot", "temp/A3/assets/megaman/megashoot.png");

}


void Assets::AddTexture(const std::string& name, const std::string& path)
{
  sf::Texture tex;
  m_Textures.emplace(name, tex);
}

void Assets::addAnimation(const std::string& name, const std::string& path)
{
  sf::Texture tex;

  if (!tex.loadFromFile(path))
  {
    std::cout << "Texture failed to load: " << name << std::endl;
  }

  Animation* ani = new Animation(name, tex);

  m_Animations.emplace(name, *ani);
}

void Assets::addSound(const std::string& name, const std::string& path)
{
  sf::SoundBuffer buffer;

  if(!buffer.loadFromFile("path"))
    std::cout << "Failed to load sound: " << name << std::endl;

  sf::Sound sound;

  sound.setBuffer(buffer);

  m_Sounds.emplace(name, sound);
}

void Assets::addFont(const std::string& name, const std::string& path)
{
  sf::Font font;

  if (!font.loadFromFile(path))
    std::cout << "Failed to load font: " << name << std::endl;

  m_Fonts.emplace(name, font);
}
