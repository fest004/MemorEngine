#pragma once

#include "entity.hpp"
#include <memory>
#include <vector>
#include <map>

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec>     EntityMap; 

class EntityManager
{
  public:
    //Methods
    EntityManager();

    bool init();
    void update();

    void removeDeadEntities(EntityVec& vec);

    std::shared_ptr<Entity> addEntity(const std::string& tag);

    const EntityVec& getEntities();
    const EntityVec& getEntities(const std::string& tag);


  public:
    //Variables
   
  private:
    //Methods


  private:
    //Variables
    EntityVec m_Entities;
    EntityVec m_EntitiesToAdd;
    EntityMap m_EntityMap; 
    size_t m_totalEntities;
};
