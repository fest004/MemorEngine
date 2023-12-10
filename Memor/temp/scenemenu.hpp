#pragma once

#include "../memor.h"
#include <SFML/Graphics/RectangleShape.hpp>

class SceneMenu : public Scene
{

public:
  SceneMenu(const SceneMenu &) = default;
  SceneMenu(SceneMenu &&) = default;
  SceneMenu &operator=(const SceneMenu &) = default;
  SceneMenu &operator=(SceneMenu &&) = default;
  SceneMenu(MemorGame *gameEngine);

protected:

  sf::Font m_Font;
  sf::Text m_Text;
  bool m_DrawTextures = true;
  int m_Selection = 0;

  //TODO REMOVE, TEMP

  math::vec2 tempPos;
  math::vec2 tempSize;


private:
  bool init();
  void update();
  void sNavbar(int i);
  void sSelect();
  void sDoAction(const Action& action);
  void sRender();
  void onEnd();
  void drawLine(const math::vec2& v1, const math::vec2& v2);
  int getSelection();


  void createPlayer();

  LockedCam lockedCam;

  math::vec2 m_Pos;

  sf::RectangleShape m_Rectangle;
  
};
