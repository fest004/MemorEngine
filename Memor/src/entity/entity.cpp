#include "entity.hpp"



Entity::Entity(const size_t id, const std::string tag)
:
m_ID(id),
m_Tag(tag)
{
  std::cout << "Entity Constructor \n";
}

bool Entity::isActive()
{
  return m_Active;
}

const std::string Entity::getTag()
{
  return m_Tag;
}


const size_t Entity::getID()
{
  return m_ID;
}

void Entity::destroy()
{

}


