#include "entitymanager.hpp"
#include <memory>

EntityManager::EntityManager()
{

}

bool EntityManager::init()
{
  
}

void EntityManager::update()
{

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
