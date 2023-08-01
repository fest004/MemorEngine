#pragma once

#include "component.hpp"

class CInput : public Component
{
  public:
    //Methods
    CInput() {}

  public:
  //Variables
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool shoot = false;
    bool jump = false;
};
