#include "entity.hpp"

// Implementation of Entity Constructor
Entity::Entity(const size_t id, const std::string tag)
:
m_ID(id),
m_Tag(tag)
{}

// Implementation of isActive method
bool Entity::isActive()
{
    return m_Active;
}

// Implementation of getTag method
const std::string Entity::getTag()
{
    return m_Tag;
}

// Implementation of getID method
const size_t Entity::getID()
{
    return m_ID;
}

// Implementation of destroy method
void Entity::destroy()
{
    m_Active = false;
}

// Note: The other methods are template methods and can't be implemented in the source file.
// Template methods are usually implemented right in the header file because C++ requires 
// the full method body to be visible at the point of invocation.

