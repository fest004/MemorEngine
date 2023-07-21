#pragma once

#include <iostream>
#include <memory.h>
#include <memory>

#include "../components/components.hpp"

class EntityManager;

typedef std::tuple<
CTransform, 
CLifespan,
CInput,
CBoundingBox,
CAnimation,
CGravity,
CState
> ComponentTuple;

class Entity
{
   friend class EntityManager;

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
    }

    template<typename T>
    T& getComponent()
    {
      return std::get<T>(m_Components);
    }

    template<typename T>
    T& getComponent() const
    {
      return std::get<T>(m_Components);
    }

    template<typename T>
    void removeComponent()
    {
      getComponent<T>() = T();
    }





 public:
    //Variables

 private:
    //Methods
    // Private constructor so only the entitymanager can create
    Entity(const size_t id, const std::string tag);

 private:
    //Variables
    std::string m_Tag    = "default";
    bool        m_Active = true;
    size_t      m_ID     = 0;
    ComponentTuple m_Components;


};
