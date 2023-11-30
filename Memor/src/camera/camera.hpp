#include "../entity/ecs.hpp"
#include "../math/math.hpp"
#include <SFML/Graphics/View.hpp>
#include <SFML/Main.hpp>

class Camera {
public:
  // Methods
  Camera(math::vec2 position, math::vec2 size);
  Camera(math::vec2* ent, math::vec2 size);
  Camera(math::vec2* ent, math::vec2 size, float rotation);
  Camera(math::vec2 position, math::vec2 size, float rotation);
  Camera(math::vec2 position, float roation);

  virtual void cameraUpdate() = 0;
  
  float getRotation() { return m_Rotation; }
  void setRotation(float rotation) { m_Rotation = rotation; };

  math::vec2 getSize() { return m_Size; }
  void setSize(math::vec2 size) { m_Size = size; }

  math::vec2 setPosition() { return m_Position; }
  void getPosition(math::vec2 position) { m_Position = position; }

  void setEntity(math::vec2* ent) { m_EntityToFollow = ent; }

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

  math::vec2* m_EntityToFollow;
};
