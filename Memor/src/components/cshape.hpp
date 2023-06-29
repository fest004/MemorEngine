#pragma once

#include "../math/math.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>


class CShape
{
  public:
    //Methods
    CShape(float radius, int points, const sf::Color& fillColor, const sf::Color& outlineColor, float outlineThickness) 
    : circle(radius, points)
  {
    circle.setFillColor(fillColor);
    circle.setOutlineColor(outlineColor);
    circle.setOutlineThickness(outlineThickness);
  }

  public: 
    //Variables
    sf::CircleShape circle;
};