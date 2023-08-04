#include "component.hpp"
#include <iostream>


class CState : public Component
{
  public:
    CState() {}
    CState(const std::string& s)
    :
    m_State(s)
    {}

    std::string m_State = "ground";
    float m_JumpTimer = 0.0f;
};
