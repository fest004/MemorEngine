// A3 WORK
#include "memor.hpp"


MemorGame::MemorGame(const std::string& filename)
{

}


void MemorGame::run()
{

}

void MemorGame::quit()
{

}

bool MemorGame::init(const std::string& path)
{
  return true;
}

void MemorGame::update()
{

}

void MemorGame::sUserInput()
{


}


std::shared_ptr<Scene> MemorGame::currentScene()
{
  return m_SceneMap[m_CurrentScene];
}


Assets& MemorGame::getAssets() 
{
  return m_Assets;
}


void changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene = false)
{

}


