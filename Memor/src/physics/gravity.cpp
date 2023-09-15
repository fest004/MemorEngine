#include "gravity.hpp"
#include "../memorlogger/logger.hpp"


namespace physics
{


bool UpdateGravity(std::shared_ptr<Entity> e)
{


  if (!e->hasComponent<CTransform>()) {
    MemorWarn("UpdateGravity argument {} does not have a CBoundingBox component! Method will return false", e->getTag());
    return false;
  }

  if (!e->hasComponent<CGravity>()) {
    MemorWarn("UpdateGravity argument {} does not have a CBoundingBox component! Method will return false", e->getTag());
    return false;
  }

  auto& gravity = e->getComponent<CGravity>();
  auto& transform = e->getComponent<CTransform>();

// Unsure if it should apply a variable maxGravity/maxVelocity or if it should take an entities maxVelocity variable (which is not created yet)


  if (transform.m_Velocity.y + gravity.m_Gravity < gravity.m_MaxVelocity)
  {
    transform.m_Velocity.y += gravity.m_Gravity;
    return true;
  }
  else
  {
    transform.m_Velocity.y = gravity.m_MaxVelocity;
    return true;
  }

  return true;
}

/*

Unsure if it should apply any forces here or not, or if it should all be applied somewhere else. Commented out for now

bool ApplyGravity(std::shared_ptr<Entity> e)
{
  if (!e->hasComponent<CTransform>()) {
    MemorWarn("ApplyGravity argument {} does not have a CBoundingBox component! Method will return false", e->getTag());
    return false;
  }

  if (!e->hasComponent<CGravity>()) {
    MemorWarn("ApplyGravity argument {} does not have a CBoundingBox component! Method will return false", e->getTag());
    return false;
  }

  return true;
}
*/

}

