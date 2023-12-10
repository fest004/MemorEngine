#include "camera.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>

Camera::Camera() 
: 
m_Position(math::vec2(0, 0)), 
m_Size(math::vec2(1, 1)), 
m_Rotation(0.0f) 
{
  // Initialize the view with default values
  m_View.setCenter(sf::Vector2f(0.0f, 0.0f));
  m_View.setSize(sf::Vector2f(1.0f, 1.0f));
}


Camera::Camera(math::vec2 position, math::vec2 size, float rotation)
: 
m_Position(position), 
m_Size(size), 
m_Rotation(rotation) 
{

}
