#include "entitymanager.hpp"
#include <memory>

EntityManager::EntityManager()
{

}

// Updates EntityVec and EntityMap 
void EntityManager::update()
{
  for (auto e : m_EntitiesToAdd) 
  {
    m_Entities.push_back(e);
    m_EntityMap[e->m_Tag].push_back(e);
  }

  m_EntitiesToAdd.clear();

  //remove dead entities
  removeDeadEntities(m_Entities);

  for (auto& [tag, EntityVec] : m_EntityMap) {
    removeDeadEntities(EntityVec);
  }

}

void EntityManager::removeDeadEntities(EntityVec& entities)
{
  entities.erase(std::remove_if(entities.begin(), entities.end(), [](const std::shared_ptr<Entity>& entity) 
  {
    return !entity->m_Active;
  }
  ), entities.end());
}

//Adds entity to a vec of entites to add, then it actually gets added at start of every frame by update method
std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag)
{
  auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));

  m_EntitiesToAdd.push_back(entity);

  return entity;
}

//Returns all entities
const EntityVec& EntityManager::getEntities()
{
  return m_Entities;
}

// Returns entities with given tag
const EntityVec& EntityManager::getEntities(const std::string &tag)
{
  return m_EntityMap[tag];
}


