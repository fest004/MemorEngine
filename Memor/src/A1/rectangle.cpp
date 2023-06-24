#include "rectangle.hpp"

Rectangle::Rectangle(std::string name, int xPos, int yPos, float xSpeed, float ySpeed, sf::Color color, sf::Vector2f size)
: 
m_xSpeed  (xSpeed), 
m_ySpeed  (ySpeed), 
m_Name    (name) 
{
  rect = sf::RectangleShape(size);
  rect.setFillColor(color);
  rect.setPosition(xPos, yPos);
  rect.setSize(size);
}

void Rectangle::CheckCollision(int windowWidth, int windowHeight) {
  if (rect.getPosition().x < 0 || rect.getPosition().x + rect.getSize().x > windowWidth) 
  {
    m_xSpeed = -m_xSpeed;
  }

  if (rect.getPosition().y < 0 || rect.getPosition().y + rect.getSize().y > windowHeight) 
  {
    m_ySpeed = -m_ySpeed;
  }
}

void Rectangle::Move() {
  // rect.move(m_xSpeed, m_ySpeed);
  rect.setPosition(rect.getPosition().x - m_xSpeed, rect.getPosition().y - m_ySpeed);
}

void Rectangle::Draw(sf::RenderWindow& window, sf::Text txt)
  {
    sf::FloatRect textRect = txt.getLocalBounds();
    txt.setOrigin(textRect.left + textRect.width /2.0f, textRect.top + textRect.height / 2.0f);
    txt.setPosition(rect.getPosition().x + (rect.getSize().x / 2 ), rect.getPosition().y + (rect.getSize().y / 2.0f));


    window.draw(rect);
    window.draw(txt);
  }


