#include "camera.hpp"

Camera::Camera(math::vec2 position, math::vec2 size)
:
m_Position(position),
m_Size(size)
{}

Camera::Camera(math::vec2* ent, math::vec2 size)
:
m_EntityToFollow(ent),
m_Size(size)
{}

Camera::Camera(math::vec2* ent, math::vec2 size, float rotation)
:
m_EntityToFollow(ent),
m_Size(size),
m_Rotation(rotation)
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

