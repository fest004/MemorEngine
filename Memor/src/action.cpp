#include "action.hpp"
#include <sstream>

Action::Action() {}

Action::Action(const std::string &name, const std::string &type)
    : m_Name(name), m_Type(type) {}

const std::string &Action::getName() const { return m_Name; }

const std::string &Action::getType() const { return m_Type; }

