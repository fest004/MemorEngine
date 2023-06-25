#include "circle.hpp"

Circle::Circle(std::string name, int xPos, int yPos, float xSpeed, float ySpeed, sf::Color color, int radius)
: 
m_xSpeed  (xSpeed), 
m_ySpeed  (ySpeed), 
m_Name    (name) 
{
  m_Circle = sf::CircleShape(radius);
  m_Circle.setFillColor(color);
  m_Circle.setPosition(xPos, yPos);
}

void Circle::CheckCollision(int windowWidth, int windowHeight) {
  if (m_Circle.getPosition().x < 0 || m_Circle.getPosition().x + (m_Circle.getRadius()* 2) > windowWidth) 
  {
    m_xSpeed = -m_xSpeed;
  }

  if (m_Circle.getPosition().y < 0 || m_Circle.getPosition().y + (m_Circle.getRadius() * 2) > windowHeight) 
  {
    m_ySpeed = -m_ySpeed;
  }
}

void Circle::Move() {
  // rect.move(m_xSpeed, m_ySpeed);
  m_Circle.setPosition(m_Circle.getPosition().x - m_xSpeed, m_Circle.getPosition().y - m_ySpeed);
}

void Circle::Draw(sf::RenderWindow& window, sf::Text txt)
  {
    txt.setString(m_Name);
    sf::FloatRect textRect = txt.getLocalBounds();
    txt.setOrigin(textRect.left + textRect.width /2.0f, textRect.top + textRect.height / 2.0f);
    txt.setPosition(m_Circle.getPosition().x + m_Circle.getRadius(), m_Circle.getPosition().y + m_Circle.getRadius());


    window.draw(m_Circle);
    window.draw(txt);
  }


