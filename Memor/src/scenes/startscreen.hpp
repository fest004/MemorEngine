#pragma once

#include "scene.hpp"

class StartScreen: public Scene
{

public:
  StartScreen(MemorGame* gameEngine);


private:

  sf::Font m_Font;
  sf::Text m_Text;
  bool m_IsOver;

  bool init();
  void update();
  void sRender();
  void sDoAction(const Action& action);


};
