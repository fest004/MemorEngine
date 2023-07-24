// #pragma once
//
// #include <iostream>
// #include <memory>
// #include <unordered_map>
// #include <typeindex>
//
// #include "../components/components.hpp"
//
// class EntityManager;
//
// class Entity
// {
//    friend class EntityManager;
//
//   public:
//     //Methods
//     bool isActive();
//     const std::string getTag();
//     const size_t getID();
//     void destroy();
//
//     template <typename T>
//     bool hasComponent() const
//     {
//       return m_Components.count(typeid(T)) > 0;
//     }
//
//     template <typename T, typename... TArgs>
//     T& addComponent(TArgs&&... mArgs)
//     { 
//         auto component = std::make_shared<T>(std::forward<TArgs>(mArgs)...);
//         component->has = true;
//         m_Components[typeid(T)] = component;
//         return *component;
//     }
//
//     template<typename T>
//     T& getComponent()
//     {
//         return *std::static_pointer_cast<T>(m_Components.at(typeid(T)));
//     }
//
//     template<typename T>
//     void removeComponent()
//     {
//         m_Components.erase(typeid(T));
//     }
//
//  private:
//     // Private constructor so only the entitymanager can create
//     Entity(const size_t id, const std::string tag);
//
//  private:
//     //Variables
//     std::string m_Tag    = "default";
//     bool        m_Active = true;
//     size_t      m_ID     = 0;
//     std::unordered_map<std::type_index, std::shared_ptr<Component>> m_Components;
// };
//
