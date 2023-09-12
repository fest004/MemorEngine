#include "assets.hpp"
#include "animation.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Texture.hpp>

void Assets::loadFromFile(const std::string &path) {
  std::cout << "LoadFromFile" << std::endl;
  // TODO Load assets lmao

  addAnimation("Question", "temp/A3/assets/question2.png", 2, 5);
  addAnimation("QuestionHit", "temp/A3/assets/questionhit.png");
  addAnimation("Brick", "temp/A3/assets/brick.png");
  addAnimation("BaseBrick", "temp/A3/assets/basebrick.png");
  addAnimation("Ground", "temp/A3/assets/ground.png");
  addAnimation("Shoot", "temp/A3/assets/megaman/megashoot.png");
  addAnimation("Up", "temp/A3/assets/megaman/megaup.png");
  addAnimation("Down", "temp/A3/assets/megaman/megadown.png");
  addAnimation("Standing", "temp/A3/assets/megaman/megastand.png", 3, 10);
  addAnimation("Running", "temp/A3/assets/megaman/megarun.png", 4, 25);
  addAnimation("Goomba", "temp/A3/assets/goombawalk.png", 2, 4);
  addAnimation("GoombaStomp", "temp/A3/assets/goombastomp.png");
  addAnimation("Hill", "temp/A3/assets/hill.png");
  addAnimation("BigCloud", "temp/A3/assets/bigcloud.png");
  addAnimation("SmallCloud", "temp/A3/assets/smallcloud.png");
  addAnimation("Coin", "temp/A3/assets/coin.png", 13, 200);
  addAnimation("ScoreCoin", "temp/A3/assets/coin.png", 13, 30);
  addAnimation("Bullet", "temp/A3/assets/megaman/attackred.png", 3, 10);
  addAnimation("Flagpole", "temp/A3/assets/flagpole.png");




}

void Assets::AddTexture(const std::string &name, const std::string &path) {
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
    std::cout << "Failure" << std::endl;

  auto result = m_Textures.insert(std::make_pair(name, tex));

  // If the insertion was successful, create the animation using the texture
  // from the map
  if (result.second) // Check if the insertion was successful
  {
    const sf::Texture &textureRef =
        result.first->second; // Get a reference to the texture from the map
    Animation ani(name, textureRef, frameCount, speed);
    m_Animations.insert(std::make_pair(name, ani));
  }
}



void Assets::addSound(const std::string &name, const std::string &path) {
  sf::SoundBuffer buffer;

  if (!buffer.loadFromFile("path"))
    std::cout << "Failed to load sound: " << name << std::endl;

  sf::Sound sound;

  sound.setBuffer(buffer);

  m_Sounds.insert(std::make_pair(name, sound));
}

void Assets::addFont(const std::string &name, const std::string &path) {
  sf::Font font;

  if (!font.loadFromFile(path))
    std::cout << "Failed to load font: " << name << std::endl;

  m_Fonts.insert(std::make_pair(name, font));
}
