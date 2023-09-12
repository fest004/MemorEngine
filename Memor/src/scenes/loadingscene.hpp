#include "scene.hpp"

class LoadingScene : public Scene
{

  LoadingScene(MemorGame* gameEngine);



private:

  sf::Font m_Font;
  sf::Text m_Text;
  bool m_IsOver;

  void update();
  void sRender();


};
