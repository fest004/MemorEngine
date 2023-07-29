#pragma once

#include "math/vec2.hpp"
#include "scene.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <map>
#include <memory>
#include "action.hpp"

#include "entity/entitymanager.hpp"

class SceneMenu : public Scene
{

public:

SceneMenu(MemorGame* gameEngine);

protected:

  sf::Font m_Font;
  sf::Text m_Text;
  bool m_DrawTextures = true;
  int m_Selection = 0;


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
};
