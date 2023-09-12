#pragma once

#include "renderables/assets.hpp"
#include "scenes/scene.hpp"
#include <memory>
#include "memorlogger/log.hpp"
#include "memorlogger/logger.hpp"
#include <fstream>


class MemorGame
{
  protected:
    bool init(const std::string& path);
    void update();
    void sUserInput();
    std::shared_ptr<Scene> currentScene();

  public:
    MemorGame(const std::string& path);
    void changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene = false);
    void quit();
    void run();

    //Getters and setters
  sf::RenderWindow& getWindow();
  Assets& getAssets();
  bool isRunning();

  protected:
sf::RenderWindow m_Window;
    Assets m_Assets;
    std::string m_CurrentScene;
    std::map<std::string, std::shared_ptr<Scene>> m_SceneMap; // string name : shared_ptr Scene
    size_t m_SimulationSpeed = 1;
    bool m_Running = true;

    Log MemorLogger;


  private:
	std::fstream m_KeyLogger;
	void Replay();

};
