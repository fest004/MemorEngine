#include "detection.hpp"
#include "../components/components.hpp"
#include "../math/math.hpp"
#include "../memorlogger/logger.hpp"

namespace physics {


math::vec2 GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
  
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

  if(a->hasComponent<CBoundingBox>() && b->hasComponent<CBoundingBox>()) {

    float dx = abs(a->getComponent<CTransform>().m_PrevPos.x - b->getComponent<CTransform>().m_PrevPos.x);
    float dy = abs(a->getComponent<CTransform>().m_PrevPos.y - b->getComponent<CTransform>().m_PrevPos.y);

    auto boundingBoxA = a->getComponent<CBoundingBox>();
    auto boundingBoxB = b->getComponent<CBoundingBox>();

    return math::vec2(boundingBoxA.m_HalfSize.x - boundingBoxB.m_HalfSize.x - dx, boundingBoxA.m_HalfSize.y - boundingBoxB.m_HalfSize.y - dy);
  }
  return math::vec2(0, 0);
}


bool IsOverlapping(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
  math::vec2 overlap = GetOverlap(a, b);

  if (!a->hasComponent<CBoundingBox>()) {
    MemorWarn("IsOverlap argument {} does not have a CBoundingBox component! Method will return false", a->getTag());
  }

if (!b->hasComponent<CBoundingBox>()) {
    MemorWarn("IsOverlap argument {} does not have a CBoundingBox component! Method will return false", b->getTag());
  }
  

  
  if (overlap.x > 0 && overlap.y >0) 
    return true;

  return false;
}

} //end namespace physics
