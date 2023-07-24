#pragma once

#include "component.hpp"
#include "../math/math.hpp"


class CBoundingBox : public Component
{
  public:

  CBoundingBox() {}
  CBoundingBox(const math::vec2& size) 
  :
  m_Size(size),
  m_HalfSize(size.x / 2, size.y / 2)
  {}

    //Variables
    math::vec2 m_Size;
    math::vec2 m_HalfSize;
};
