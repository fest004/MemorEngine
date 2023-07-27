#pragma once

#include "component.hpp"
#include "../math/math.hpp"
#include <SFML/Graphics.hpp>


class CTransform : public Component
{
  public:
    //Methods
    CTransform() {}

    CTransform(const math::vec2& pos) 
    :
    m_Pos(pos)
    {}

    CTransform(const math::vec2& pos, const math::vec2& vel, float angle)
    :
    m_Pos(pos),
    m_Velocity(vel),
    m_Angle(angle)
    {}


    CTransform(const math::vec2& pos, const math::vec2& vel, const math::vec2 scale)
    :
    m_Pos(pos),
    m_Velocity(vel),
    m_Scale(scale)
    {}

  public: 
    //Variables
    math::vec2 m_Pos = {0,0};
    math::vec2 m_PrevPos = {0, 0};
    math::vec2 m_Scale = {1, 1};
    math::vec2 m_Velocity = {0,0};
    float m_Angle;
};
