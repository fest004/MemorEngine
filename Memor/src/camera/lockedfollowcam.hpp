#pragma once

#include "camera.hpp"


class LockedCam : public Camera
{

  public:

  LockedCam();
  LockedCam(const math::vec2& entityPos, const math::vec2& size);



  
  void cameraUpdate(sf::RenderWindow& window);
  void setEntity(math::vec2& ent) { m_EntityPos = ent; }

  private:

  void updatePosition();

  math::vec2 m_EntityPos;
};





