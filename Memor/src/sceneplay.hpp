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

  math::vec2 m_GridSize = { 64.0f, 64.0f };
  std::shared_ptr<Entity> m_Player;
  std::string m_LevelPath;
  PlayerConfig m_PlayerConfig;
  bool m_DrawTextures = true;
  bool m_DrawCollision = false;
  bool m_DrawGrid = true;
  sf::Text m_GridText;


private:
  bool init(const std::string& levelPath);
  void loadLevel(const std::string& filename);
  void spawnPlayer();
  void spawnBullet(std::shared_ptr<Entity> entity);
  void update();
  void sMovement();
  void sLifespan();
  void sCollision();
  void sDoAction(const Action& action);
  void sAnimation();
  void sRender();
  void onEnd();
  void togglePause();
  void drawLine(const math::vec2& v1, const math::vec2& v2);


  math::vec2 gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);



};
