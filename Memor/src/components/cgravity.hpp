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

  private:
    float m_Gravity = 0;
    

};