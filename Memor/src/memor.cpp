// A3 WORK
#include "memor.hpp"
#include "action.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <memory>
#include <string>
#include "scenes/startscreen.hpp"

#define TEST_REPLAY 0

// ATM filename does not really do anything, might be usefull later but probable removing
MemorGame::MemorGame(const std::string& filename)
{
	init(filename);
}

bool MemorGame::init(const std::string& path)
{
	MemorLogger.Init();
	MemorInfo("Memor Engine Started!");

	m_Window.create(sf::VideoMode(1280, 768), "Mega Mario");
	m_Window.setFramerateLimit(60);

	m_KeyLogger.open("test.txt");
	

	changeScene("STARTSCREEN", std::make_shared<StartScreen>(this));

  return true;
}

void MemorGame::run(const std::string& name, std::shared_ptr<Scene> scene)
{
  addInitialScene(name, scene);

  while (isRunning())
  {
    update();
  }

}

void MemorGame::quit()
{
	MemorLogger.Shutdown();
	m_KeyLogger.close();
	m_Running = false;
}

void MemorGame::update()
{
	if (currentScene()->hasEnded())
	  changeScene("MENUSCENE", m_SceneMap["MENUSCENE"]);

	sUserInput();
	currentScene()->update();
}

void MemorGame::sUserInput()
{

	sf::View view = m_Window.getDefaultView();

 sf::Event event;
	while (m_Window.pollEvent(event)) 
	{
		if (event.type == sf::Event::Closed) 
		{
			quit();
		}



   if (event.type == sf::Event::Resized)
		{
			sf::View view
		  (
    		sf::Vector2f(static_cast<float>(m_Window.getSize().x) / 2, static_cast<float>(m_Window.getSize().y) / 2),
    	  sf::Vector2f(static_cast<float>(m_Window.getSize().x), static_cast<float>(m_Window.getSize().y))
	    );

	    m_Window.setView(view);
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::X)
		  {
		    MemorInfo("Screenshot saved!")
		  	sf::Texture texture;
		  	texture.create(m_Window.getSize().x, m_Window.getSize().y);
		  	texture.update(m_Window);
		  	if (texture.copyToImage().saveToFile("test.png"))
		    {
		    MemorInfo("Screenshot saved!")
		  	}
		  }
		}

		#if !TEST_REPLAY

		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
	  {
	  	if(currentScene()->getActionMap().find(event.key.code) == currentScene()->getActionMap().end()) { continue; }

	  	MemorInfo(std::to_string(event.key.code));
	  	std::cout << m_KeyLogger.is_open() << std::endl;
			m_KeyLogger << std::to_string(event.key.code) << "\n";
			m_KeyLogger.flush();

	  	const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";

	  	currentScene()->sDoAction(Action(currentScene()->getActionMap().at(event.key.code), actionType));

		}
		else 
	  {
			m_KeyLogger << "\n";
			m_KeyLogger.flush();
		}

#else 
		std::string line;

		while (std::getline(m_KeyLogger, line)) 
		{
	  	const std::string actionType = "START";
	  	if (line == "") continue;
	  	currentScene()->sDoAction(Action(currentScene()->getActionMap().at(std::stoi(line)), actionType));
		}



#endif
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
		MemorCritical("Scene does not exist: {}", sceneName);
		return;
	}

	}

	if (endCurrentScene) 
	{
		m_SceneMap.erase(m_SceneMap.find(m_CurrentScene));
	}
	m_CurrentScene = sceneName;
}




void MemorGame::addInitialScene(const std::string& name, std::shared_ptr<Scene> scene) 
{
  m_SceneMap[name] = scene; // Add the scene to the map
}
