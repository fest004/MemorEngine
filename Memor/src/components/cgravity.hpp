#pragma once

#include "component.hpp"
#include "../math/math.hpp"


class CGravity : public Component
{
  public:
  CGravity() {}
  CGravity(float gravity)
  :
  m_Gravity(gravity)
  {}

  float m_Gravity = 0;
    

};
