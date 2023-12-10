#pragma once

#include "camera.hpp"

class LockedCam : public Camera 
{
  public:

  LockedCam()
  : Camera() 
  {
  }


  ~LockedCam();


  LockedCam(math::vec2 position, math::vec2 size, float rotation = 0.0f);

  void cameraUpdate(); // Implement this method

  // Method to set the target to follow
  void setTarget(math::vec2& targetPosition);


private:
  math::vec2* m_targetPosition; // Position of the target to follow
};
