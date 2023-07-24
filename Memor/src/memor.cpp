// A3 WORK
#include "memor.hpp"
#include "action.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/VideoMode.hpp>
#include "sceneplay.hpp"


MemorGame::MemorGame(const std::string& filename)
{
	init(filename);
}

bool MemorGame::init(const std::string& path)
{
	m_Assets.loadFromFile(path);

	m_Window.create(sf::VideoMode(1280, 768), "Mega Mario");
	m_Window.setFramerateLimit(60);

	changeScene("MENU", std::make_shared<ScenePlay>(this, "levelPath.txt"));


  return true;
}

void MemorGame::run()
{
	while (isRunning())
  {
		update();
	}

}

void MemorGame::quit()
{
	m_Running = false;
}

void MemorGame::update()
{

}

void MemorGame::sUserInput()
{
 sf::Event event;
	while (m_Window.pollEvent(event)) 
	{
		if (event.type == sf::Event::Closed) 
		{
			quit();
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::X)
		  {
		  	std::cout << "Screenshot saved to" << "test.png" << std::endl;
		  	sf::Texture texture;
		  	texture.create(m_Window.getSize().x, m_Window.getSize().y);
		  	texture.update(m_Window);
		  	if (texture.copyToImage().saveToFile("test.png"))
		    {
		  	std::cout << "Screenshot saved to" << "test.png" << std::endl;
		  	}
		  }
		}

		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
	  {
	  	if(currentScene()->getActionMap().find(event.key.code) == currentScene()->getActionMap().end()) { continue; }

	  	const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";

	  	currentScene()->doAction(Action(currentScene()->getActionMap().at(event.key.code), actionType));

		}
	}
}

sf::RenderWindow& MemorGame::getWindow()
{
	return m_Window;
}


std::shared_ptr<Scene> MemorGame::currentScene()
{
  return m_SceneMap[m_CurrentScene];
}


Assets& MemorGame::getAssets() 
{
  return m_Assets;
}

bool MemorGame::isRunning()
{
	return m_Running && m_Window.isOpen();
}




void MemorGame::changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene)
{
if (scene != nullptr) 
{
		m_SceneMap[sceneName] = scene;
}
else
	{
	if (m_SceneMap.find(sceneName) == m_SceneMap.end()) 
	{
		std::cout << "Scene " << sceneName << " does not exist!" << std::endl;
		return;
	}

	}

	if (endCurrentScene) 
	{
		m_SceneMap.erase(m_SceneMap.find(m_CurrentScene));
	}

	m_CurrentScene = sceneName;
}
