#include "../entity/ecs.hpp"

class Physics
{
public:
//Methods
math::vec2 GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
math::vec2 GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);


};
