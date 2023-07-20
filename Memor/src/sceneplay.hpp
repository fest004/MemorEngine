#pragma once

#include "scene.hpp"
#include <map>
#include <memory>

#include "entity/entitymanager.hpp"

class Scene_Play : public Scene
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


private:
  bool init(std::string& filename);
  void loadLevel(const std::string& filename);
  void spawnPlayer();
  void spawnBullet();
  void update();
  void sMovement();
  void sLifespan();
  void sCollision();
  void sDoAction(const Action& action);
  void sAnimation();
  void sRender();



};
