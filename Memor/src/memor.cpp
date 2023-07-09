#include "memor.hpp"
#include "components/ctransform.hpp"
#include "math/vec2.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <fstream>
#include <memory>
#include <string>
#include "entity/entitymanager.hpp"

Memor::Memor(const std::string& filepath)
{
  init(filepath);
}

bool Memor::init(std::string path)
{
  std::ifstream fileIn(path);

  // TODO Finish all structs. Add Error handling (Return bool success)
  fileIn >> m_PlayerConfig.SR >> m_PlayerConfig.SR; //Continue this pattern until for all structs for all values


  m_Window.create(sf::VideoMode(1280, 720), "Memor");
  m_Window.setFramerateLimit(60);

  if (!m_Font.loadFromFile("fonts/arcadeclassic.ttf")) {
    std::cout << "Font not found" << std::endl;
    return false;
  }

  m_Text.setFont(m_Font);
  m_Text.setFillColor(sf::Color::White);
  m_Text.setCharacterSize(15);
  m_Text.setString("Score: ");
  m_Text.setPosition(10, m_Text.getGlobalBounds().height - 10);
  

  spawnPlayer();
  return true;
}

void Memor::Run()
{
  //TODO Add pause functionality

  while (m_Running)
  {
    m_Entities.update();

    update();
    sEnemySpawner();
    sUserInput();
    sMovement();
    sCollision();
    sRender();
    sLifeSpan();
    m_CurrentFrame++;
  }
}


void Memor::update()
{
  std::string tempScore = "Score: ";
  tempScore = "Score: " + std::to_string(m_Score);
  m_Text.setString(tempScore);
}

// Systems
void Memor::sMovement()
{
  //All entity movement in this method 
  //Read cInput to determine if player is moving
  
  //All player movement
  // Setting velocity to 0 every frame so movement stops if cInput is false 
  m_Player->cTransform->m_Velocity = {0, 0};
  
  if (m_Player->cInput->up)
  {
    m_Player->cTransform->m_Velocity.y += -5;
  }

  if (m_Player->cInput->left)
  {
    m_Player->cTransform->m_Velocity.x += -5;
  }

  if (m_Player->cInput->down)
  {
    m_Player->cTransform->m_Velocity.y += +5;
  }

  if (m_Player->cInput->right)
  {
    m_Player->cTransform->m_Velocity.x += +5;
  }


  m_Player->cTransform->m_Pos.x += m_Player->cTransform->m_Velocity.x;
  m_Player->cTransform->m_Pos.y += m_Player->cTransform->m_Velocity.y;

  //Entity movement
  for (auto enemy : m_Entities.getEntities("enemy")) 
  {
    enemy->cTransform->m_Pos += enemy->cTransform->m_Velocity;
  }

 for (auto enemy : m_Entities.getEntities("bullet")) 
  {
    enemy->cTransform->m_Pos += enemy->cTransform->m_Velocity;
  }

 for (auto smallEnemy : m_Entities.getEntities("smallEnemy")) 
  {
    smallEnemy->cTransform->m_Pos += smallEnemy->cTransform->m_Velocity;
  }







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
    // Pressing input 
    if (event.type == sf::Event::KeyPressed)
    {
      switch (event.key.code)
      {
        case sf::Keyboard::W:
          m_Player->cInput->up = true;
          break;
        case sf::Keyboard::A:
          m_Player->cInput->left = true;
          break;
        case sf::Keyboard::S:
          m_Player->cInput->down = true;
          break;
        case sf::Keyboard::D:
          m_Player->cInput->right = true;
          break;
        case sf::Keyboard::P:
          std::cout << "Paused" << "\n";
          m_Paused = !m_Paused;
        case sf::Keyboard::Escape:
          m_Running = false;
        default:
            break;
      }
    }

    //When keys are released 
if (event.type == sf::Event::KeyReleased)
    {
      switch (event.key.code)
      {
        case sf::Keyboard::W:
          m_Player->cInput->up = false;
          break;
        case sf::Keyboard::A:
          m_Player->cInput->left = false;
          break;
        case sf::Keyboard::S:
          m_Player->cInput->down = false;
          break;
        case sf::Keyboard::D:
          m_Player->cInput->right = false;
          break;
        default:
          break;
      }
    }


//Mouse actions
if (event.type == sf::Event::MouseButtonPressed) 
{
  if (event.mouseButton.button == sf::Mouse::Left)
  {
    spawnBullet(m_Player, math::vec2(event.mouseButton.x, event.mouseButton.y));
  }

}

  }

}
void Memor::sLifeSpan()
{
  //Lifespan mechanic
  //
  

  //TODO add way to check if entity has certain component

  for (auto e : m_Entities.getEntities()) 
  {

    if (e->cLifespan != nullptr) {
    if (e->cLifespan->m_Remaining > 0) 
    {
      sf::Color fillColor = e->cShape->circle.getFillColor();
      sf::Color outLineColor= e->cShape->circle.getOutlineColor();
      
      float alphaRatio = static_cast<float>(e->cLifespan->m_Remaining) / e->cLifespan->m_Total;

      fillColor.a = static_cast<sf::Uint8>(255 * alphaRatio);
      outLineColor.a = static_cast<sf::Uint8>(255 * alphaRatio);

      e->cShape->circle.setFillColor(fillColor);
      e->cShape->circle.setOutlineColor(outLineColor);

      e->cLifespan->m_Remaining--;
    } else {

      if (e->getTag() == "smallEnemy")
        m_Score += e->cScore->m_Score;

      e->destroy();
    }
  }

  /* for all entities
   * if entity has no lifespan component, skip it
   * if entity has > 0 lifespan, subtract 1
   * if it has lifespan and is alive, scale alpha channel
   * if lifespan is up, destroy the entity
   */
  }

}

void Memor::sRender()
{
  m_Window.clear();


  for (auto e : m_Entities.getEntities())
  {
    e->cShape->circle.setPosition(e->cTransform->m_Pos.x, e->cTransform->m_Pos.y);

    e->cTransform->m_Angle += 1.0f;
    e->cShape->circle.setRotation(e->cTransform->m_Angle);

    m_Window.draw(e->cShape->circle);
  }

  m_Window.draw(m_Text);
  m_Window.display();

}

void Memor::sEnemySpawner()
{
  // TODO code that implements spawning should go here
  if (m_CurrentFrame - m_LastEnemySpawnTime > 60)
    spawnEnemy();

}

void Memor::sCollision()
{
  //TODO
  //Implement all collisions using collision RADIUS

  for (auto& enemy : m_Entities.getEntities("enemy"))
  {
    float xPos = enemy->cTransform->m_Pos.x;
    float yPos = enemy->cTransform->m_Pos.y;
    float radius = enemy->cShape->circle.getRadius();

    // Collision / bouncing for entities that != player
    // X plane collision with walls 
    if (xPos - radius < 0 || xPos + radius > m_Window.getSize().x)
    {
      enemy->cTransform->m_Velocity.x = -enemy->cTransform->m_Velocity.x;
    }

    //Y plane collision with walls
    if (yPos - radius < 0 || yPos + radius > m_Window.getSize().y)
    {
      enemy->cTransform->m_Velocity.y = -enemy->cTransform->m_Velocity.y;
    }

    //Player and enemy collision
    float distanceBeetweenCirclesSQ =                                                                                                                                                                          
        (m_Player->cTransform->m_Pos.x - enemy->cTransform->m_Pos.x) * (m_Player->cTransform->m_Pos.x - enemy->cTransform->m_Pos.x) +
        (m_Player->cTransform->m_Pos.y - enemy->cTransform->m_Pos.y) * (m_Player->cTransform->m_Pos.y - enemy->cTransform->m_Pos.y);
                                                                                                                                                               
    if (distanceBeetweenCirclesSQ < (enemy->cShape->circle.getRadius() + m_Player->cShape->circle.getRadius()) * (enemy->cShape->circle.getRadius() + m_Player->cShape->circle.getRadius())) {
        enemy->destroy();
        m_Player->destroy();
        spawnPlayer();
    }

    for (auto bullet : m_Entities.getEntities("bullet")) {
      float distanceBeetweenCirclesSQ =                                                                                                                                                                          
          (bullet->cTransform->m_Pos.x - enemy->cTransform->m_Pos.x) * (bullet->cTransform->m_Pos.x - enemy->cTransform->m_Pos.x) +
          (bullet->cTransform->m_Pos.y - enemy->cTransform->m_Pos.y) * (bullet->cTransform->m_Pos.y - enemy->cTransform->m_Pos.y);
                                                                                                                                                                 
      if (distanceBeetweenCirclesSQ < (enemy->cShape->circle.getRadius() + bullet->cShape->circle.getRadius()) * (enemy->cShape->circle.getRadius() + bullet->cShape->circle.getRadius())) {
          enemy->destroy();
          bullet->destroy();
          spawnSmallEnemies(enemy);
          m_Score += enemy->cScore->m_Score;
      }

    }
  }

  //Smallenemies and player
 for (auto& smallEnemy : m_Entities.getEntities("smallEnemy"))
  {
    float xPos = smallEnemy->cTransform->m_Pos.x;
    float yPos = smallEnemy->cTransform->m_Pos.y;
    float radius = smallEnemy->cShape->circle.getRadius();

    float distanceBeetweenCirclesSQ =                                                                                                                                                                          
        (m_Player->cTransform->m_Pos.x - smallEnemy->cTransform->m_Pos.x) * (m_Player->cTransform->m_Pos.x - smallEnemy->cTransform->m_Pos.x) +
        (m_Player->cTransform->m_Pos.y - smallEnemy->cTransform->m_Pos.y) * (m_Player->cTransform->m_Pos.y - smallEnemy->cTransform->m_Pos.y);
                                                                                                                                                               
      if (distanceBeetweenCirclesSQ < (smallEnemy->cShape->circle.getRadius() + m_Player->cShape->circle.getRadius()) * (smallEnemy->cShape->circle.getRadius() + m_Player->cShape->circle.getRadius())) {
        smallEnemy->destroy();
        m_Player->destroy();
        spawnPlayer();
    }



  }


  // Player xPos window bounds
  if (m_Player->cTransform->m_Pos.x - m_Player->cShape->circle.getRadius() < 0)
    {
      m_Player->cTransform->m_Pos.x = 0 + m_Player->cShape->circle.getRadius();
    } else if (m_Player->cTransform->m_Pos.x + m_Player->cShape->circle.getRadius() > m_Window.getSize().x) {
      m_Player->cTransform->m_Pos.x = m_Window.getSize().x - m_Player->cShape->circle.getRadius();
    }


  // Player yPos window bounds
  if (m_Player->cTransform->m_Pos.y - m_Player->cShape->circle.getRadius() < 0)
    {
      m_Player->cTransform->m_Pos.y = 0 + m_Player->cShape->circle.getRadius();
    } else if (m_Player->cTransform->m_Pos.y + m_Player->cShape->circle.getRadius() > m_Window.getSize().y) {
      m_Player->cTransform->m_Pos.y = m_Window.getSize().y - m_Player->cShape->circle.getRadius();
    }

}

void Memor::spawnPlayer()
{
  auto entity = m_Entities.addEntity("player");

  entity->cTransform = std::make_shared<CTransform>(math::vec2(m_Window.getSize().x / 2.0f, m_Window.getSize().y / 2.0f), math::vec2(1.0f, 1.0f), 0.0f);

  entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 255, 0), 4.0f);

  entity->cInput = std::make_shared<CInput>();

  m_Player = entity;

}

void Memor::spawnEnemy()
{
  //TODO make enemies spawn within the rules of the config
  
  auto entity = m_Entities.addEntity("enemy");

  entity->cTransform = std::make_shared<CTransform>(math::vec2(500.0f, 500.0f), math::vec2(2.0f, 2.0f), 0.0f);

  entity->cShape = std::make_shared<CShape>(12.0f, 5, sf::Color(100, 50, 10), sf::Color(255, 155, 0), 4.0f);

  entity->cScore = std::make_shared<CScore>(entity->cShape->circle.getPointCount() * 100);




  m_LastEnemySpawnTime = m_CurrentFrame;

}

void Memor::spawnSmallEnemies(std::shared_ptr<Entity> e) {
  //TODO make small enemies spread sides/360 degress 
    int sides = e->cShape->circle.getPointCount();
    float theta = 360.0f / sides;

    for (int i = 0; i < sides; i++) {
        auto entity = m_Entities.addEntity("smallEnemy");

        float angle = i * theta;
        float radians = angle * 3.14159f / 180.0f;

        float xPos = e->cTransform->m_Pos.x + e->cShape->circle.getRadius() * std::cos(radians);
        float yPos = e->cTransform->m_Pos.y + e->cShape->circle.getRadius() * std::sin(radians);

        entity->cTransform = std::make_shared<CTransform>(math::vec2(xPos, yPos), math::vec2(std::cos(radians), std::sin(radians)), radians);
        entity->cLifespan = std::make_shared<CLifespan>(100);

        entity->cShape = std::make_shared<CShape>(e->cShape->circle.getRadius() / 2, sides, e->cShape->circle.getFillColor(), e->cShape->circle.getOutlineColor(), 4.0f);
        entity->cShape->circle.setRotation(radians);


        entity->cScore = std::make_shared<CScore>((entity->cShape->circle.getPointCount() * 100) * 2);
    }
}


void Memor::spawnBullet(std::shared_ptr<Entity> e, const math::vec2& target)
{
  auto bullet = m_Entities.addEntity("bullet");

  math::vec2 direction = target - m_Player->cTransform->m_Pos; 
  float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
  direction.x /= length;
  direction.y /= length;

  float bulletSpeed = 5.0f;

  direction.x *= bulletSpeed;
  direction.y *= bulletSpeed;

  bullet->cTransform = std::make_shared<CTransform>(m_Player->cTransform->m_Pos, direction, 0);
  bullet->cShape = std::make_shared<CShape>(10, 8, sf::Color(255, 255, 255), sf::Color(255, 0, 0), 2);
  bullet->cLifespan = std::make_shared<CLifespan>(100);
}

void Memor::spawnSpecialWeapon(std::shared_ptr<Entity> e)
{

}
