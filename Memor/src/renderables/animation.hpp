#pragma once


#include <vector>
#include "../math/math.hpp"
#include <SFML/Graphics.hpp>

class Animation {
public:
//Methods
Animation();
Animation(const std::string& name, const sf::Texture& t);
Animation(const std::string& name, const sf::Texture& t, size_t frameCount, size_t speed);

void update();
bool hasEnded() const;

const std::string &getName() const;
const math::vec2& getSize() const;
sf::Sprite& getSprite();


private:
//Variables
  sf::Sprite m_Sprite;
  size_t m_FrameCount = 1; // total number of frames of animation
  size_t m_CurrentFrame = 0; // the current frame of animation being played
  size_t m_Speed = 0; // the speed to play this animation
  math::vec2 m_Size = {1, 1}; // the size of the animation frame
  std::string m_Name;
};
