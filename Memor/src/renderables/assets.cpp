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

void Assets::addSound(const std::string& name, const std::string& path) 
{
	sf::SoundBuffer sound;

	if (!sound.loadFromFile(path)) 
	{
		std::cerr << "Could not load sound file: " << path << std::endl;
	}
	else 
	{
		m_Buffers[name] = sound;
		m_Sounds[name] = sf::Sound(m_Buffers[name]);
		// m_Sounds[name].setVolume(DEFAULT_AUDIO_VOLUME);
	}
}

void Assets::addFont(const std::string &name, const std::string &path) {
  sf::Font font;

  if (!font.loadFromFile(path))
    std::cout << "Failed to load font: " << name << std::endl;

  m_Fonts.insert(std::make_pair(name, font));
}



void Assets::playSound(const std::string& name, float volume)
{
    auto iter = m_Buffers.find(name);
    if (iter == m_Buffers.end())
    {
        MemorWarn("Attempted to play unknown sound: {}", name);
        return;
    }

    m_ActiveSounds.emplace_back();             
    sf::Sound& sound = m_ActiveSounds.back();  
    sound.setBuffer(iter->second);             
    sound.setVolume(volume);                   
    sound.play();                              
}

void Assets::playSound(const std::string& name)
{
    auto iter = m_Buffers.find(name);
    if (iter == m_Buffers.end())
    {
        MemorWarn("Attempted to play unknown sound: {}", name);
        return;
    }

    m_ActiveSounds.emplace_back();                 
    sf::Sound& sound = m_ActiveSounds.back();  
    sound.setBuffer(iter->second);             
    sound.play();                              
}




sf::Sound& Assets::getSound(const std::string& name)
{
	assert(m_Sounds.find(name) != m_Sounds.end());
	return m_Sounds.at(name);

}



void Assets::cleanupSounds()
{
    m_ActiveSounds.remove_if([](const sf::Sound& sound)
    {
        return sound.getStatus() == sf::Sound::Stopped;
    });
}
