#pragma once


#include "component.hpp"

class CLifespan : Component
{
  public:
    //Methods
    CLifespan(int total)
    :
    m_Total(total),
    m_Remaining(total)
    {}

  public:
    //Variables
    int m_Total;
    int m_Remaining;
};
