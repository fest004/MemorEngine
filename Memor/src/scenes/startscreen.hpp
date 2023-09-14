#include "scene.hpp"

class StartScreen: public Scene
{

StartScreen(MemorGame* gameEngine);


private:

  sf::Font m_Font;
  sf::Text m_Text;
  bool m_IsOver;

  void init();
  void update();
  void sRender();


};
