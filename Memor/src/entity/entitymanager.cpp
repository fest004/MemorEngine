// #include "entitymanager.hpp"
// #include <memory>
//
// EntityManager::EntityManager() : m_NextID(0) {}
//
// // Creates an entity and returns a reference to it
// std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
// {
//     auto e = Entity(m_NextID++, "tag");
//     m_Entities.emplace(e.getID(), e);
//     return std::make_shared<Entity>(e);
// }
//
// // Returns a pointer to the entity with the given ID, or nullptr if not found
// std::shared_ptr<Entity> EntityManager::getEntity(size_t id)
// {
//     auto it = m_Entities.find(id);
//     return it == m_Entities.end() ? nullptr : it->second;
// }
//
// // Deletes the entity with the given ID
// void EntityManager::destroyEntity(size_t id)
// {
//     m_Entities.erase(id);
// }
//
//
// void EntityManager::update()
// {
//
// }
