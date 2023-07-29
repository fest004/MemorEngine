#include "animation.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <cmath>

Animation::Animation()
{

}

Animation::Animation(const std::string& name, const sf::Texture& t)
: Animation(name, t, 1, 0)
{}

Animation::Animation(const std::string& name, const sf::Texture& t, size_t frameCount, size_t speed)
: 
m_Name(name),
m_Sprite(t),
m_FrameCount(frameCount),
m_CurrentFrame(0),
m_Speed(speed)
{
  m_Size = math::vec2((float)t.getSize().x / frameCount, (float)t.getSize().y);
  m_Sprite.setOrigin(m_Size.x /2.0f, m_Size.y / 2.0f);
  m_Sprite.setTextureRect(sf::IntRect(std::floor(m_CurrentFrame) * m_Size.x, 0, m_Size.x, m_Size.y));
}



//updates the animation to show the next frame, depending on its speed
//animation loops when it reaches the end
void Animation::update()
{
  //add the speed variable to the current frame

   m_CurrentFrame++;

  //TODO 
  // 1. calculate the correct frame of the animation to play based on the currentFrame and speed
  // 2. set the texture rectangle properly (see constructor for sample)

}

void Animation::setSize(math::vec2 size)
{
  sf::FloatRect spriteBounds = m_Sprite.getLocalBounds();

  // Calculate the scale factors needed to resize to the given size
  float scaleX = size.x / spriteBounds.width;
  float scaleY = size.y / spriteBounds.height;

  // Apply the scale factors to the sprite
  m_Sprite.setScale(scaleX, scaleY);
  m_Sprite.setOrigin(m_Size.x /2.0f, m_Size.y / 2.0f);
  m_Sprite.setTextureRect(sf::IntRect(std::floor(m_CurrentFrame) * m_Size.x, 0, m_Size.x, m_Size.y));
}


const math::vec2& Animation::getSize() const
{
  return m_Size;
}


const std::string& Animation::getName() const
{
  return m_Name;
}


sf::Sprite& Animation::getSprite()
{
  return m_Sprite;
}


bool Animation::hasEnded() const
{
  //TODO detect when animation has ended (last frame was played)
  return false;
}
