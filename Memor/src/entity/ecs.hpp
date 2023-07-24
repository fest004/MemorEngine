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
  CState
  > ComponentTuple;

public:
    //Methods
    bool isActive();
    const std::string getTag();
    const size_t getID();
    void destroy();

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
  CState()
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
  void addToGroup(Entity *mEntity, Group mGroup) {
    m_GroupedEntities[mGroup].emplace_back(mEntity);
  }

  std::vector<Entity *> &getGroup(Group mGroup) {
    return m_GroupedEntities[mGroup];
  }

  std::shared_ptr<Entity> addEntity(const std::string& tag) {
    Entity newEntity(m_lastID++, tag);
    return std::make_shared<Entity>(newEntity);
  }


  void update() {
    for (auto& e : m_EntitiesToDestroy)
    {
      auto i = std::find(m_Entities.begin(), m_Entities.end(), e);
      if (i != m_Entities.end())
        {
          m_Entities.erase(i);
        }
      
      m_EntitiesToDestroy.clear();
    }
  }

private:
  std::array<std::vector<Entity *>, m_MaxGroups> m_GroupedEntities;
  std::vector<std::unique_ptr<Entity>> m_Entities;
  std::vector<std::unique_ptr<Entity>> m_EntitiesToDestroy;
  size_t m_lastID = 1;
};

