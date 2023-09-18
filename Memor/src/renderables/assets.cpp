#include "assets.hpp"
#include "animation.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <utility>
#include "../memorlogger/logger.hpp"



void Assets::addTexture(const std::string &name, const std::string &path) {
  sf::Texture tex;

  if (!tex.loadFromFile(path))
    std::cout << "Texture failed to load: " << name << std::endl;

  m_Textures.insert(std::make_pair(name, tex));
}

void Assets::addAnimation(const std::string &name, const std::string &path) {
  sf::Texture tex;

  if (!tex.loadFromFile(path)) {
    std::cout << "Texture failed to load: " << name << std::endl;
    return; // Return early if texture failed to load
  }

  // Insert the texture into the map
  auto result = m_Textures.insert(std::make_pair(name, tex));

  // If the insertion was successful, create the animation using the texture
  // from the map
  if (result.second) // Check if the insertion was successful
  {
    const sf::Texture &textureRef =
        result.first->second; // Get a reference to the texture from the map
    Animation ani(name, textureRef);
    m_Animations.insert(std::make_pair(name, ani));
  }
}

void Assets::addAnimation(const std::string &name, const std::string &path, size_t frameCount, size_t speed) {
  sf::Texture tex;

  if (!tex.loadFromFile(path))
    MemorWarn("Animation {} not found!", name);

  auto result = m_Textures.insert(std::make_pair(name, tex));

  // If the insertion was successful, create the animation using the texture
  // from the map
  if (result.second) // Check if the insertion was successful
  {
    const sf::Texture &textureRef = result.first->second; // Get a reference to the texture from the map
    Animation ani(name, textureRef, frameCount, speed);
    m_Animations.insert(std::make_pair(name, ani));
  }
}



void Assets::addSound(const std::string &name, const std::string &path) 
{
 sf::SoundBuffer soundBuffer;

	if (!soundBuffer.loadFromFile(path)) 
	  MemorCritical("Sound {} not found!", name);

		m_Buffers[name] = soundBuffer;
	  sf::Sound sound;
	  sound.setBuffer(soundBuffer);
	  // sound.play();
		m_Sounds[name] = sound;
}

void Assets::addFont(const std::string &name, const std::string &path) {
  sf::Font font;

  if (!font.loadFromFile(path))
    std::cout << "Failed to load font: " << name << std::endl;

  m_Fonts.insert(std::make_pair(name, font));
}
