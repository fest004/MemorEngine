#include "scenemenu.hpp"
#include "memor.hpp"
#include "scene.hpp"
#include "sceneplay.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <string>

SceneMenu::SceneMenu(MemorGame* gameEngine)
:
Scene(gameEngine)
{
  init();
}

bool SceneMenu::init()
{
  registerAction(sf::Keyboard::W, "NAV_UP");
  registerAction(sf::Keyboard::Up, "NAV_UP");
  registerAction(sf::Keyboard::S, "NAV_DOWN");
  registerAction(sf::Keyboard::Down, "NAV_DOWN");
  registerAction(sf::Keyboard::Enter, "NAV_SELECT");
  registerAction(sf::Keyboard::Escape, "QUIT");
  registerAction(sf::Keyboard::T, "TOGGLE_TEXTURE");

  if (!m_Font.loadFromFile("fonts/arcadeclassic.ttf")) {
    std::cout << "Font nout found!" << std::endl;
    return false;
  }

  m_Text.setFont(m_Font);
  m_Text.setFillColor(sf::Color::White);
  m_Text.setCharacterSize(30);

  return true;
}

void SceneMenu::update()
{
  sRender();
}
  

void SceneMenu::sRender()
{
  m_Memor->getWindow().clear(sf::Color(100, 100, 255)); 

  if (m_DrawTextures)
  {

    for (int i = 0; i < 3; i++) 
    {
      i == m_Selection ? m_Text.setFillColor(sf::Color(50, 50, 50)) : m_Text.setFillColor(sf::Color(255, 255, 255));
      m_Text.setString("level " + std::to_string(i));
      sf::FloatRect textBounds = m_Text.getLocalBounds();
      m_Text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
      m_Text.setPosition(m_Memor->getWindow().getSize().x / 2.0f, m_Memor->getWindow().getSize().y / 2.0f + (i * 40));
      m_Memor->getWindow().draw(m_Text);
    }
  }
  m_Memor->getWindow().display();
}

void SceneMenu::sDoAction(const Action& action)
{

  if (action.getType() == "START")
  {
    std::cout << "START" << std::endl;
    if      (action.getName() == "TOGGLE_TEXTURE")      { m_DrawTextures = !m_DrawTextures; }
    else if (action.getName() == "NAV_UP")              { sNavbar(-1); }
    else if (action.getName() == "NAV_DOWN")            { sNavbar(1); }
    else if (action.getName() == "NAV_SELECT")          { sSelect(); }
    else if (action.getName() == "QUIT")                { }
  } 
  else if (action.getType() == "END")
  {
    if (action.getName() == "NAV_UP")              { std::cout << "NAVUP" << std::endl;}
    else if (action.getName() == "NAV_DOWN")       {}
  }
}

void SceneMenu::sNavbar(int i)
{
  //Navbar higlight coloring and selection
  if (i < 0) {
    if (m_Selection <= 0) {
      m_Selection = 2;
    } else {
      m_Selection--;
    }
    return;
  } 

  if (i > 0) {
    if (m_Selection >= 2) {
      m_Selection = 0;
    } else {
      m_Selection++;
    }
    return;
  }
}

void SceneMenu::sSelect()
{
	m_Memor->changeScene("ScenePlay", std::make_shared<ScenePlay>(m_Memor, "levelpath.txt"));;

}

int SceneMenu::getSelection()
{
 return m_Selection;
}

void SceneMenu::onEnd()
{

}

