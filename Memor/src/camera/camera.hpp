#pragma once

#include "../entity/ecs.hpp"
#include "../math/math.hpp"
#include <SFML/Graphics/View.hpp>
#include <SFML/Main.hpp>

class Camera {
public:
  // Methods
  Camera();
  Camera(math::vec2 size);
  Camera(math::vec2 position, math::vec2 size);
  Camera(math::vec2 position, math::vec2 size, float rotation);
  Camera(math::vec2 position, float roation);

  virtual void cameraUpdate(sf::RenderWindow& window) = 0;
  
  float getRotation() { return m_Rotation; }
  void setRotation(float rotation) { m_Rotation = rotation; };

  math::vec2 getSize() { return m_Size; }
  void setSize(math::vec2 size) 
  { 
    m_Size = size; 
    m_View.setSize(m_Size.x, m_Size.y);
  }

  math::vec2 getPosition() { return m_Position; }
  void setPosition(math::vec2 position) { m_Position = position; }

  sf::View getView() { return m_View; }

  void shake(float duration, float intensity);

private:
  // Methods

public:
  // Variables

protected:
  // Variables
  sf::View m_View;
  math::vec2 m_Position;
  math::vec2 m_Size;
  float m_Rotation;

};
