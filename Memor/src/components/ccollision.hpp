#pragma once

#include "component.hpp"
#include "../math/math.hpp"
#include <SFML/Graphics.hpp>


class CCollision : public Component
{
  public:
    //Methods
    CCollision() {}
    CCollision(float radius) 
    : m_Radius(radius) 
    {}

    CCollision(float width, float height)
    : m_Width(width),
      m_Height(height)
    {}


  public: 
    //Variables
    float m_Radius;
    float m_Width;
    float m_Height;
};
