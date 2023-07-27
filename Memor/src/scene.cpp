#include "scene.hpp"
#include "memor.hpp"

// Constructor
Scene::Scene(MemorGame* game) : m_Memor(game), m_currentFrame(0) {}

// Simulation method (TODO: Change val)
void Scene::simulate(int val) {
    // TODO: Implement simulation logic here
}

// Register an action with a specific key
void Scene::registerAction(sf::Keyboard::Key key, std::string actionName) {
    m_ActionMap[static_cast<int>(key)] = actionName;
}

// Toggle pause state
void Scene::togglePause() {
    m_Paused = !m_Paused;
}

// End the scene
void Scene::endScene() {
    m_HasEnded = true;
}


const std::map<int, std::string>& Scene::getActionMap() const
{
    return m_ActionMap;
}
