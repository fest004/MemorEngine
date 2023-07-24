#include "../entity/ecs.hpp"


namespace physics {


bool AABB(const Entity &rectangle1, const Entity &rectangle2) {
  math::vec2 rect1Pos = rectangle1.getComponent<CTransform>().m_Pos;
  math::vec2 rect2Pos = rectangle2.getComponent<CTransform>().m_Pos;

  float rect1Width = rectangle1.getComponent<CBoundingBox>().m_Size.x;
  float rect1Height = rectangle1.getComponent<CBoundingBox>().m_Size.y;


  float rect2Width= rectangle2.getComponent<CBoundingBox>().m_Size.x;
  float rect2Height= rectangle2.getComponent<CBoundingBox>().m_Size.x;

  if (rect1Pos.x >= rect2Pos.x &&
      rect2Pos.x + rect2Width >= rect1Pos.x &&
      rect1Pos.y + rect1Height >= rect2Pos.y &&
      rect2Pos.y + rect2Height >= rect1Pos.y) {
    return true;
  }
  return false;
}
}
