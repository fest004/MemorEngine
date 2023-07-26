#include "physics.hpp"
#include "../components/components.hpp"
#include "../math/math.hpp"

math::vec2 Physics::GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
  //TODO return the overlap rectangle size of the bounding boxes of entity A and entity B

  return math::vec2(0, 0);
}



math::vec2 Physics::GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b){

  //TODO return the previous overlap rectangle size of the bounding boxes of entity A and entity B
  // previous overlap uses the enties previous position


 
  return math::vec2(0, 0);
}



