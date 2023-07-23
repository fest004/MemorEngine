#pragma once

#include "component.hpp"

class CScore : public Component
{
  public: 
    //Methods
      CScore() {}
      CScore(int score)
      : m_Score(score)
      {}

  public:
    //Variables
    int m_Score;
    
};
