#include "startscreen.hpp"
#include "../memor.hpp"
#include <SFML/Graphics/Color.hpp>
#include "../utils/text.hpp"


//Start screen to be loaded at booting of any application made in Memor. Acts as a startscreen and as a mini template for any other scene

StartScreen::StartScreen(MemorGame* gameEngine)
:
Scene(gameEngine)
{
  init();
}




bool StartScreen::init()
{

  registerAction(sf::Keyboard::Space, "SKIP");
  registerAction(sf::Keyboard::P, "TOOT");

  if (!m_Font.loadFromFile("fonts/arcadeclassic.ttf")) 
  {
    MemorCritical("Font not found!")
    return false;

  }

  m_Memor->getAssets().addSound("Toot", "toot.wav");

  m_Text.setFont(m_Font);
  m_Text.setString("Memor Engine");
  m_Text.setFillColor(sf::Color::White);
  utils::ResizeText(m_Text, m_Memor->getWindow(), 20);

  return true;
}

void StartScreen::update()
{
  utils::ResizeText(m_Text, m_Memor->getWindow(), 20);
  utils::CenterText(m_Text, m_Memor->getWindow());
  sRender();
}

void StartScreen::sRender()
{
  m_Memor->getWindow().clear(sf::Color(30, 30, 30));
  m_Memor->getWindow().draw(m_Text);
  m_Memor->getWindow().display();
}

void StartScreen::sDoAction(const Action& action)
{
  if (action.getType() == "START")
  {
    if       (action.getName() == "SKIP") { m_IsOver = true; }
    else if  (action.getName() == "TOOT") { m_Memor->getAssets().getSound("Toot").play(); MemorWarn("Toot"); }
  }

}


