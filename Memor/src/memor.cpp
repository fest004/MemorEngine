#include "memor.hpp"
#include "math/vec2.hpp"
#include <SFML/Window/Event.hpp>
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
  //All entity movement in this method 
  //Read cInput to determine if player is moving
  
  // Setting velocity to 0 every frame so movement stops if cInput is false 
  m_Player->cTransform->m_Velocity = {0, 0};
  
  if (m_Player->cInput->up)
  {
    m_Player->cTransform->m_Velocity.y = -5;
  }

  m_Player->cTransform->m_Pos.x += m_Player->cTransform->m_Velocity.x;
  m_Player->cTransform->m_Pos.y += m_Player->cTransform->m_Velocity.y;

}
void Memor::sUserInput()
{
  sf::Event event; 

  while (m_Window.pollEvent(event)) 
  {
    if (event.type == sf::Event::Closed) 
    {
      m_Running = false;
    }

    if (event.type == sf::Event::KeyPressed)
    {
      switch (event.key.code)
      {
        case sf::Keyboard::W:
          std::cout << "W" << "\n";
          break;
        case sf::Keyboard::A:
          std::cout << "W" << "\n";
          break;
        case sf::Keyboard::S:
          std::cout << "W" << "\n";
          break;
        case sf::Keyboard::D:
          std::cout << "W" << "\n";
          break;
        case sf::Keyboard::P:
          m_Paused = !m_Paused;
        case sf::Keyboard::Escape:
          m_Running = false;
        default:
            break;
      }
    }
    

  }

}
void Memor::sLifeSpan()
{
  //Lifespan mechanic

  /* for all entities
   * if entity has no lifespan component, skip it
   * if entity has > 0 lifespan, subtract 1
   * if it has lifespan and is alive, scale alpha channel
   * if lifespan is up, destroy the entity
   */

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
  //TODO code that implements spawning should go here
  //
  // (m_CurrentFrame - m_LastEnemySpawnTime) to figure out when to spawn an enemy

  spawnEnemy();

}

void Memor::sCollision()
{
  //TODO
  //Implement all collisions using collision RADIUS

}

void Memor::spawnPlayer()
{
  auto entity = m_Entities.addEntity("player");

  entity->cTransform = std::make_shared<CTransform>(math::vec2(200.0f, 200.0f), math::vec2(1.0f, 1.0f), 0.0f);

  entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 255, 0), 4.0f);

  entity->cInput = std::make_shared<CInput>();

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
