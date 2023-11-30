#include "camera.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>

Camera::Camera() {}

Camera::Camera(math::vec2 position, math::vec2 size)
:
m_Position(position),
m_Size(size)
{}

Camera::Camera(math::vec2 position, math::vec2 size, float rotation)
:
m_Position(position),
m_Size(size),
m_Rotation(rotation)
{}


Camera::Camera(math::vec2 position, float rotation)
:
m_Position(position),
m_Rotation(rotation)
{}


