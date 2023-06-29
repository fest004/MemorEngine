#include "memor.hpp"
#include "math/vec2.hpp"
#include <fstream>

bool Memor::init(std::string path)
{
  std::ifstream fileIn(path);

  // TODO Finish all structs. Add Error handling (Return bool success)
  fileIn >> m_PlayerConfig.SR >> m_PlayerConfig.SR; //Continue this pattern until for all structs for all values


  m_Window.create(sf::VideoMode(1280, 720), "Memor");
  m_Window.setFramerateLimit(60);

  spawnPlayer();


  return true;
}

void Memor::Run()
{
  //TODO Add pause functionality

  while (m_Running)
  {
    m_Entities.update();

    sEnemySpawner();
    sMovement();
    sCollision();
    sUserInput();
    sRender();

    m_CurrentFrame++;
  }
}


void Memor::update()
{

}

// Systems
void Memor::sMovement()
{

}
void Memor::sUserInput()
{

}
void Memor::sLifeSpan()
{

}

void Memor::sRender()
{
  m_Window.clear();

  m_Player->cShape->circle.setPosition(m_Player->cTransform->m_Pos.x, m_Player->cTransform->m_Pos.y);

  m_Player->cTransform->m_Angle += 1.0f;
  m_Player->cShape->circle.setRotation(m_Player->cTransform->m_Angle);

  m_Window.draw(m_Player->cShape->circle);

  m_Window.display();

}

void Memor::sEnemySpawner()
{

}

void Memor::sCollision()
{

}

void Memor::spawnPlayer()
{
  auto entity = m_Entities.addEntity("player");

  entity.cTransform = std::make_shared<CTransform>(math::vec2(200.0f, 200.0f), math::vec2(1.0f, 1.0f));

  entity.cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 255, 0), 4.0f);

  entity.cInput = std::make_shared<CInput()>();

  m_Player = entity;

}

void Memor::spawnEnemy()
{
  //TODO make enemies spawn within the rules of the config

  m_LastEnemySpawnTime = m_CurrentFrame;

}

void Memor::spawnSmallEnemies(std::shared_ptr<Entity> e)
{

}

void Memor::spawnBullet(std::shared_ptr<Entity> e)
{

}

void Memor::spawnSpecialWeapon(std::shared_ptr<Entity> e)
{

}
