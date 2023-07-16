#pragma once

#include "assets.hpp"
#include "scene.hpp"
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>
#include "entity/entitymanager.hpp"
#include "entity/entity.hpp"
#include "math/vec2.hpp"
#include "utils/timer.hpp"

class Memor
{
  public:
    //Methods
   
  public:
    //Variables
    Memor(const std::string& filename);
    void Run();
    void Quit();


  private:
    //Methods
    bool init(std::string path);
    void update();

    //Systems
    void sUserInput();
    void sLifeSpan();
    void sRender();

    Scene currentScene();
    Assets getAssets();
    void changeScene();





  private:
    //Variables

    sf::RenderWindow m_Window;
    bool m_Running = true;
    Assets m_Assets;
    std::string m_CurrentScene;
    std::unordered_map<std::string, Scene> m_Scenes;

    std::shared_ptr<Entity> m_Player;
};
