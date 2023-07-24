// #pragma once
//
// #include <map>
// #include <memory>
// #include "entity.hpp"
//
// class EntityManager
// {
// public:
//     EntityManager();
//
//     // Creates an entity and returns a reference to it
//     std::shared_ptr<Entity> addEntity(const std::string& tag);
//
//     // Returns a pointer to the entity with the given ID, or nullptr if not found
//     std::shared_ptr<Entity> getEntity(size_t id);
//
//     // Deletes the entity with the given ID
//     void destroyEntity(size_t id);
//
//     void update();
//
// private:
//     std::map<size_t, std::shared_ptr<Entity>> m_Entities;
//     size_t m_NextID;
// };
