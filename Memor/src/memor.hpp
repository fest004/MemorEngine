#pragma once

#include "renderables/assets.hpp"
#include "scene.hpp"
#include <memory>


class MemorGame
{
  protected:
    sf::RenderWindow m_Window;
    Assets m_Assets;
    std::string m_CurrentScene;
    std::map<std::string, std::shared_ptr<Scene>> m_SceneMap; // string name : shared_ptr Scene
    size_t m_SimulationSpeed = 1;
    bool m_Running = true;

    bool init(const std::string& path);
    void update();

    void sUserInput();

    std::shared_ptr<Scene> currentScene();

  public:
    MemorGame(const std::string& path);

    void changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene = false);

    void quit();
    void run();

  sf::RenderWindow& getWindow();
    Assets& getAssets();
    bool isRunning();
};
