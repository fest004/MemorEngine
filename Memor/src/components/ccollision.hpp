#pragma once

#include "../math/math.hpp"
#include <SFML/Graphics.hpp>


class CCollision
{
  public:
    //Methods
    CCollision(float radius) 
    : m_Radius(radius) 
    {}


  public: 
    //Variables
    float m_Radius;
};
