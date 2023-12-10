#include "lockedfollowcam.hpp"
#include <SFML/Window/Window.hpp>


LockedCam::LockedCam(math::vec2 position, math::vec2 size, float rotation)
: 
Camera(position, size, rotation) 
{
    // Initialize the view based on the position and size
    m_View.setCenter(sf::Vector2f(m_Position.x, m_Position.y));
    m_View.setSize(sf::Vector2f(m_Size.x, m_Size.y));
    m_View.setRotation(rotation);
}



LockedCam::~LockedCam()
{
    // delete m_targetPosition;
}

void LockedCam::cameraUpdate() 
{
    m_View.setCenter(sf::Vector2f(m_targetPosition->x, m_targetPosition->y));
}

void LockedCam::setTarget(math::vec2& targetPosition) 
{
    m_targetPosition = &targetPosition;
}

