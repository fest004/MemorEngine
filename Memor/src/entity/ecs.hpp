#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <memory>
#include <vector>
#include "../components/components.hpp"

class Component;
class Entity;
class EntityManager;

using ComponentID = std::size_t;
using Group = std::size_t;



constexpr std::size_t m_MaxComponents = 32;
constexpr std::size_t m_MaxGroups = 32;

using ComponentBitSet = std::bitset<m_MaxComponents>;
using GroupBitSet = std::bitset<m_MaxGroups>;

using ComponentArray = std::array<Component *, m_MaxComponents>;

class Entity {

  friend EntityManager;

  typedef std::tuple<
  CTransform,
  CLifespan,
  CInput,
  CBoundingBox,
  CAnimation,
  CGravity,
  CState,
  CShape
  > ComponentTuple;

public:
 
    //Methods
    bool isActive() { return m_Active; }
    const std::string getTag() { return m_Tag; }
    const size_t getID() { return m_ID; }


    template <typename T>
    bool hasComponent() const
    {
      return getComponent<T>().has;
    }

    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs)
    { 
      auto& component = getComponent<T>(); 
      component = T(std::forward<TArgs>(mArgs)...);
      component.has = true;
      return component;
    }

    template<typename T>
    T& getComponent()
    {
      return std::get<T>(m_Components);
    }

    template<typename T>
    const T& getComponent() const
    {
      return std::get<T>(m_Components);
    }



    template<typename T>
    void removeComponent()
    {
      getComponent<T>() = T();
    }

 private:
    //Methods
    // Private constructor so only the entitymanager can create
  Entity(size_t id, const std::string tag)
  :
  m_Tag(tag),
  m_ID(id),
  m_Components(
  CTransform(),
  CLifespan(),
  CInput(),
  CBoundingBox(),
  CAnimation(),
  CGravity(),
  CState(),
  CShape()
  )
  {}

  

 private:
    //Variables
    std::string m_Tag    = "default";
    bool        m_Active = true;
    size_t      m_ID     = 0;
    ComponentTuple m_Components;
};

class EntityManager {


public:
  EntityManager() { std::cout << "Entitymanager created! " << std::endl; }


  void addToGroup(Entity *mEntity, Group mGroup) {
    m_GroupedEntities[mGroup].emplace_back(mEntity);
  }

  std::vector<Entity *> &getGroup(Group mGroup) {
    return m_GroupedEntities[mGroup];
  }


  std::vector<std::shared_ptr<Entity>>& getEntities() {
    return m_EntitiesVector;
  }

  std::vector<std::shared_ptr<Entity>>& getEntities(const std::string& tag) {
    return m_EntityMap[tag];
  }


  
  std::shared_ptr<Entity> addEntity(const std::string& tag) {
    auto newEntity = Entity(m_lastID++, tag);
    auto sharedEnt = std::make_shared<Entity>(newEntity);
    m_EntitiesToAdd.push_back(sharedEnt);
    return sharedEnt;
}


void destroyEntity(std::shared_ptr<Entity> e) { m_EntitiesToDestroy.push_back(e); };

 void update() 
{
  for (auto& e :m_EntitiesToAdd) 
    {
      m_EntitiesVector.push_back(e);
      m_EntityMap[e->getTag()].push_back(e);
    }
    m_EntitiesToAdd.clear();


  for (auto& e : m_EntitiesToDestroy) 
    {
      auto i = std::find(m_EntitiesVector.begin(), m_EntitiesVector.end(), e);
      if (i != m_EntitiesVector.end()) {
          m_EntitiesVector.erase(i);
        std::cout << "Deleted" << std::endl;
    }

      auto mapIter = m_EntityMap.find(e->getTag());
      if (mapIter != m_EntityMap.end()) {
        auto& entityList = mapIter->second;
        auto listerIter = std::find(entityList.begin(), entityList.end(), e);
        if (listerIter != entityList.end()) {
          entityList.erase(listerIter);
        }
      }
  }
  m_EntitiesToDestroy.clear();
}


private:
  std::array<std::vector<Entity *>, m_MaxGroups> m_GroupedEntities;
  std::vector<std::shared_ptr<Entity>> m_EntitiesVector;
  std::vector<std::shared_ptr<Entity>> m_EntitiesToDestroy;
  std::vector<std::shared_ptr<Entity>> m_EntitiesToAdd;
  std::map<std::string, std::vector<std::shared_ptr<Entity>>> m_EntityMap;
  size_t m_lastID = 1;
};

