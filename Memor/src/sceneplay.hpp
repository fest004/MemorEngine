#pragma once

#include "math/vec2.hpp"
#include "scene.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <map>
#include <memory>
#include "action.hpp"

#include "entity/entitymanager.hpp"

class ScenePlay : public Scene
{
  struct PlayerConfig
  {
    float X, Y, CX, CY, SPEED, MAXSPEED, JUMP, GRAVITY;
    std::string WEAPON;
  };

public:

  ScenePlay(MemorGame* gameEngine, const std::string& levelPath);

protected:

  sf::Font m_Font;
  sf::Text m_Text;
  math::vec2 m_GridSize = { 32.0f, 32.0f };
  std::shared_ptr<Entity> m_Player;
  std::string m_LevelPath;
  PlayerConfig m_PlayerConfig;
  bool m_DrawTextures = true;
  bool m_DrawCollision = false;
  bool m_DrawGrid = false;


private:
  bool init(std::string& levelPath);
  void loadLevel(std::string& filename);
  void spawnPlayer();
  void spawnBullet(std::shared_ptr<Entity> entity);
  void update();
  void sScore();
  void sMovement();
  void sLifespan();
  void sCollision();
  void sDoAction(const Action& action);
  void sAnimation();
  void sPlayerState();
  void sRender();
  void onEnd();
  void togglePause();
  void drawLine(const math::vec2& v1, const math::vec2& v2);
  math::vec2 gridToPixel(math::vec2 gridPos);
  math::vec2 gridToMidPixel(math::vec2 gridPos, std::shared_ptr<Entity> entity);

  int m_Score;



};
