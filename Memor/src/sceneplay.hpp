#pragma once

#include "scene.hpp"
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

protected:

  std::shared_ptr<Entity> m_Player;
  std::string m_LevelPath;
  PlayerConfig m_PlayerConfig;
  bool m_DrawTextures = false;
  bool m_DrawCollision = false;
  bool m_DrawGrid = false;
  sf::Text m_GridText;
  EntityManager m_EntityManager;


private:
  ScenePlay(MemorGame* gameEngine, const std::string& levelPath);
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


  math::vec2 gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);



};
