#pragma once

#include "../math/math.hpp"
#include <SFML/Graphics.hpp>


class CTransform
{
  public:
    //Methods
    CTransform(const math::vec2& pos, const math::vec2& vel, float angle)
    :
    m_Pos(pos),
    m_Velocity(vel),
    m_Angle(angle)
    {}

  public: 
    //Variables
    math::vec2 m_Pos = {0,0};
    math::vec2 m_Velocity = {0,0};
    float m_Angle;
};
