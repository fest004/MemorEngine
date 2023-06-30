#include "entitymanager.hpp"
#include <memory>

EntityManager::EntityManager()
{

}

bool EntityManager::init()
{
  
  return true;
}

void EntityManager::update()
{
  //TODO add entities from m_EntitieToAdd to the proper locations
  // - add them to vector of all entities
  // - add them to vector of entities with specific tag in map
  for (auto e : m_EntitiesToAdd) 
  {
    m_Entities.push_back(e);
  }

  m_EntitiesToAdd.clear();

  //remove dead entities
  removeDeadEntities(m_Entities);

  for (auto& [tag, EntityVec] : m_EntityMap) {
    removeDeadEntities(EntityVec);

  }

}

void EntityManager::removeDeadEntities(EntityVec &vec)
{

}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag)
{
  auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));

  m_EntitiesToAdd.push_back(entity);

  return entity;

}

const EntityVec& EntityManager::getEntities()
{
  return m_Entities;
}

const EntityVec& EntityManager::getEntities(const std::string &tag)
{
  //TODO Return entities with given tag argument

  return m_Entities;
}
