#include "physics.hpp"
#include "../components/components.hpp"
#include "../math/math.hpp"

namespace physics {


math::vec2 GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
  //TODO return the overlap rectangle size of the bounding boxes of entity A and entity B
  
  if(a->hasComponent<CBoundingBox>() && b->hasComponent<CBoundingBox>()) {

    float dx = abs(a->getComponent<CTransform>().m_Pos.x - b->getComponent<CTransform>().m_Pos.x);
    float dy = abs(a->getComponent<CTransform>().m_Pos.y - b->getComponent<CTransform>().m_Pos.y);

    auto boundingBoxA = a->getComponent<CBoundingBox>();
    auto boundingBoxB = b->getComponent<CBoundingBox>();

    return math::vec2(boundingBoxA.m_HalfSize.x + boundingBoxB.m_HalfSize.x - dx, boundingBoxA.m_HalfSize.y + boundingBoxB.m_HalfSize.y - dy);
  }
  return math::vec2(0, 0);
}



math::vec2 GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b){

  //TODO return the previous overlap rectangle size of the bounding boxes of entity A and entity B
  // previous overlap uses the enties previous position
  //

  if(a->hasComponent<CBoundingBox>() && b->hasComponent<CBoundingBox>()) {

    float dx = abs(a->getComponent<CTransform>().m_PrevPos.x - b->getComponent<CTransform>().m_PrevPos.x);
    float dy = abs(a->getComponent<CTransform>().m_PrevPos.y - b->getComponent<CTransform>().m_PrevPos.y);

    auto boundingBoxA = a->getComponent<CBoundingBox>();
    auto boundingBoxB = b->getComponent<CBoundingBox>();

    return math::vec2(boundingBoxA.m_HalfSize.x - boundingBoxB.m_HalfSize.x - dx, boundingBoxA.m_HalfSize.y - boundingBoxB.m_HalfSize.y - dy);
  }
  return math::vec2(0, 0);
}

}
