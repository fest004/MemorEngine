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

  std::cout << m_Name << std::endl;
  std::cout << m_FrameCount << std::endl;
  std::cout << "Before m_CurrentFrame: " << m_CurrentFrame << std::endl;
    // Increment the current frame based on speed
    m_Speed++;
    
    // Check if the animation has reached the end, if so reset it
    if (m_Speed > 15) {
        m_Speed = 0;
        m_CurrentFrame += 1;
        if (m_CurrentFrame >= m_FrameCount) { m_CurrentFrame = 0; m_HasEnded = true; }
    }
    
  // std::cout << m_Name << std::endl;
  std::cout << "After m_CurrentFrame: " << m_CurrentFrame << std::endl;
  // std::cout << "m_Speed: " << m_Speed << std::endl;
  // std::cout << "m_FrameCount: " << m_FrameCount << std::endl;

    // Calculate the x position of the texture rectangle
    int textureX = m_CurrentFrame * m_Size.x;

    // Set the texture rectangle based on the current frame
    m_Sprite.setTextureRect(sf::IntRect(textureX, 0, m_Size.x, m_Size.y));
    m_Sprite.setOrigin(m_Size.x /2.0f, m_Size.y / 2.0f);



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
  return m_HasEnded;
}
