#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Glsl.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Window/Window.hpp>


//Rect Name XPos YPos SX SY R G B W H

class Rectangle
{
  public:
  //Methods
  Rectangle(std::string name, int xPos, int yPos, float xSpeed, float ySpeed, sf::Color color, sf::Vector2f size);
  void CheckCollision(int windowWidth, int windowHeight);
  void Move();
  void Draw(sf::RenderWindow& window, sf::Text txt);

  float getYSpeed() { return m_ySpeed; }
  float getXSpeed() { return m_xSpeed; }
 
  private: 
    //Variables
    sf::RectangleShape rect;
    std::string m_Name;
    sf::Text m_Text;
    float m_xSpeed;
    float m_ySpeed;
    sf::Color m_Color;
    float m_Width;
};
