#include "lockedfollowcam.hpp"
#include <SFML/Window/Window.hpp>

LockedCam::LockedCam()
{

}

LockedCam::LockedCam(const math::vec2& entPos, const math::vec2& size)
{

}


void LockedCam::cameraUpdate(sf::RenderWindow& window)
{
  m_View.setSize(sf::Vector2f(m_Size.x, m_Size.y));
  m_View.setCenter(sf::Vector2f(m_Position.x, m_Position.y));
  window.setView(m_View);
}


