#include "scenemenu.hpp"
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
  registerAction(sf::Keyboard::A, "MOVE_LEFT");
  registerAction(sf::Keyboard::D, "MOVE_RIGHT");

  if (!m_Font.loadFromFile("fonts/arcadeclassic.ttf")) {
    std::cout << "Font nout found!" << std::endl;
    return false;
  }

  m_Text.setFont(m_Font);
  m_Text.setFillColor(sf::Color::White);
  m_Text.setCharacterSize(30);

  //tempPos = {300, 0};
  tempSize = {1920, 1080};

  createPlayer();

  lockedCam.setSize(tempSize);
  lockedCam.setTarget(m_Pos);


  return true;
}


void SceneMenu::createPlayer()
{
  m_Rectangle.setPosition(100, 100);
  m_Rectangle.setSize(sf::Vector2f(100, 100));
  m_Pos = math::vec2(m_Rectangle.getPosition().x, m_Rectangle.getPosition().y);
}

void SceneMenu::update()
{

  m_Pos = math::vec2(m_Rectangle.getPosition().x, m_Rectangle.getPosition().y);
    lockedCam.setTarget(m_Pos);
    lockedCam.cameraUpdate();


    // std::cout << "Camera position is; " << lockedCam.getPosition() << std::endl;
    // std::cout << "Text position is; " << m_Text.getPosition().x << ", " << m_Text.getPosition().x  << std::endl;
  
    m_Memor->getWindow().setView(lockedCam.getView());
    sRender();
}

void SceneMenu::sRender()
{
  m_Memor->getWindow().clear(sf::Color(100, 100, 255)); 


  if (m_DrawTextures)
  {

    for (int i = 0; i < 3; i++) 
    {
	// Change fill color of currently selected level
      i == m_Selection ? m_Text.setFillColor(sf::Color(50, 50, 50)) : m_Text.setFillColor(sf::Color(255, 255, 255));
      m_Text.setString("level " + std::to_string(i));
      // Centering text
      sf::FloatRect textBounds = m_Text.getLocalBounds();
      m_Text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
      m_Text.setPosition(m_Memor->getWindow().getSize().x / 2.0f, m_Memor->getWindow().getSize().y / 2.0f + (i * 40));
      m_Memor->getWindow().draw(m_Text);
      
        m_Memor->getWindow().draw(m_Rectangle);
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


    else if (action.getName() == "MOVE_LEFT")                { m_Rectangle.move(5, 0);  }
    else if (action.getName() == "MOVE_RIGHT")                {  m_Rectangle.move(0, 5); }
  } 
  else if (action.getType() == "END")
  {
    if (action.getName() == "NAV_UP")              {}
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
	// Will be configured to change scene to correct level path accordingly
	//m_Memor->changeScene("ScenePlay", std::make_shared<ScenePlay>(m_Memor, "temp/A3/level" + std::to_string(getSelection()) + ".txt" ));; //PSEUDO CODE
	printf("%d %c", getSelection(), '\n');
}

int SceneMenu::getSelection()
{
 return m_Selection;
}

void SceneMenu::onEnd()
{

}
