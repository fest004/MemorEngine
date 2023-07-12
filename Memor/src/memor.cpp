// A2 FINISHED AND WORKING


#include "memor.hpp"
#include "components/ctransform.hpp"
#include "entity/entitymanager.hpp"
#include "math/vec2.hpp"
#include "utils/generaterandom.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>

Memor::Memor(const std::string &filepath) { init(filepath); }

bool Memor::init(std::string path) {

  // init method reads from config file and creates Player, Enemy and Bullet Struct,
  // as well as the font data and window configuration

  std::ifstream fileIn(path);

  // Window 800 600 60 0  // W H L FS
  // Font fonts/arcadeclassic.ttf 18 255 255 255  F S R G B
  // Player 32 32 5 5 5 5 255 255 0 0 4 8 // SR CR S FR FG FB OR OG OB IT V
  // Enemy 32 32 3 3 255 255 255 2 3 8 90 60  // SR CR SMIN SMAX OR OG OB OT
  // VMMIN VMAX L SP Bullet 10 10 20 255 255 255 255 255 255 2 20 90 // SR CR S
  // FR FB OR OG OB OT V L


  std::ifstream configFile(path);
  std::string line;
  while (std::getline(configFile, line)) {
    std::istringstream iss(line);
    std::string token;
    iss >> token;

    if (token == "Window") {
      int width, height, fps, fs;
      iss >> width >> height >> fps >> fs;

      if (fs)
        m_Window.create(sf::VideoMode(width, height), "Memor", sf::Style::Fullscreen);

      m_Window.create(sf::VideoMode(width, height), "Memor");
      m_Window.setFramerateLimit(fps);

    } else if (token == "Font") {
      std::string fontPath;
      int size;
      int r, g, b;
      iss >> fontPath >> size >> r >> g >> b;

      if (!m_Font.loadFromFile(fontPath)) {
        std::cout << "Font not found" << std::endl;
        return false;
      }

      m_Text.setFont(m_Font);
      m_Text.setFillColor(sf::Color(r, g, b));
      m_Text.setCharacterSize(size);
      m_Text.setString("Score: ");
      m_Text.setPosition(10, m_Text.getGlobalBounds().height - 10);

    } else if (token == "Player") {

      // Player 32 32 5 5 5 5 255 255 0 0 4 8 // SR CR S FR FG FB OR OG OB OT V
      iss >> m_PlayerConfig.SR >> m_PlayerConfig.CR >> m_PlayerConfig.S >>
          m_PlayerConfig.FR >> m_PlayerConfig.FB >> m_PlayerConfig.FB >>
          m_PlayerConfig.OR >> m_PlayerConfig.OG >> m_PlayerConfig.OB >>
          m_PlayerConfig.OT >> m_PlayerConfig.V;

    } else if (token == "Enemy") {
      // Enemy 32 32 3 3 255 255 255 2 3 8 90 60  // SR CR SMIN SMAX OR OG OB OT
      // VMMIN VMAX L SP
      iss >> m_EnemyConfig.SR >> m_EnemyConfig.CR >> m_EnemyConfig.SMIN >>
          m_EnemyConfig.SMAX >> m_EnemyConfig.OR >> m_EnemyConfig.OG >>
          m_EnemyConfig.OB >> m_EnemyConfig.OT >> m_EnemyConfig.VMIN >>
          m_EnemyConfig.VMAX >> m_EnemyConfig.SP;

    } else if (token == "Bullet") {

      // Bullet 10 10 20 255 255 255 255 255 255 2 20 90 // SR CR S FR FB OR OG OB OT V L 
      iss >> m_BulletConfig.SR >> m_BulletConfig.CR >> m_BulletConfig.S >>
          m_BulletConfig.FR >> m_BulletConfig.FR >> m_BulletConfig.FB >>
          m_BulletConfig.OR >> m_BulletConfig.OG >> m_BulletConfig.OB >>
          m_BulletConfig.OT >> m_BulletConfig.V >> m_BulletConfig.L;
    }
  }
  configFile.close();



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

  m_SpecialCD.reset();
  return true;
}

void Memor::Run() {
  // TODO Add pause functionality

  while (m_Running) {
    if (!m_Paused) {


    m_Entities.update();
    update();
    sEnemySpawner();
    sMovement();
    sCollision();
    sLifeSpan();
    }

    sRender();
    m_CurrentFrame++;
    sUserInput();
  }
}

void Memor::update() {
  std::string tempScore = "Score: ";
  tempScore = "Score: " + std::to_string(m_Score);
  m_Text.setString(tempScore);


  for (auto e : m_Entities.getEntities()) 
  {
    e->cShape->circle.setPosition(e->cTransform->m_Pos.x, e->cTransform->m_Pos.y);
    e->cTransform->m_Angle += 1.0f;
    e->cShape->circle.setRotation(e->cTransform->m_Angle);
  }


}

void Memor::sMovement() {
  // All entity movement in this method
  // Read cInput to determine if player is moving


  //Player movement

  //  Setting velocity to 0 every frame so movement stops if cInput is false
  m_Player->cTransform->m_Velocity = {0, 0};


  //Adding player current speed to the player position

  if (m_Player->cInput->up) {
    m_Player->cTransform->m_Velocity.y += -m_PlayerConfig.S;
  }

  if (m_Player->cInput->left) {
    m_Player->cTransform->m_Velocity.x += -m_PlayerConfig.S;

  }

  if (m_Player->cInput->down) {
    m_Player->cTransform->m_Velocity.y += +m_PlayerConfig.S;

  }

  if (m_Player->cInput->right) {
    m_Player->cTransform->m_Velocity.x += +m_PlayerConfig.S;

  }

  m_Player->cTransform->m_Pos.x += m_Player->cTransform->m_Velocity.x;
  m_Player->cTransform->m_Pos.y += m_Player->cTransform->m_Velocity.y;

// Entity movement, adding its own velocity to its position
  for (auto enemy : m_Entities.getEntities("enemy")) {
    enemy->cTransform->m_Pos += enemy->cTransform->m_Velocity;
  }

  for (auto enemy : m_Entities.getEntities("bullet")) {
    enemy->cTransform->m_Pos += enemy->cTransform->m_Velocity;
  }

  for (auto smallEnemy : m_Entities.getEntities("smallEnemy")) {
    smallEnemy->cTransform->m_Pos += smallEnemy->cTransform->m_Velocity;
  }
}


void Memor::sUserInput() {
  sf::Event event;

  while (m_Window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      m_Running = false;
    }
    // Pressing input
    if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {
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
        m_Paused = !m_Paused;
        break;
      case sf::Keyboard::Escape:
        m_Running = false;
      default:
        break;
      }
    }

    // When keys are released
    if (event.type == sf::Event::KeyReleased) {
      switch (event.key.code) {
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

    // Mouse actions
    if (event.type == sf::Event::MouseButtonPressed) {
      if (event.mouseButton.button == sf::Mouse::Left) {
        spawnBullet(m_Player, math::vec2(event.mouseButton.x, event.mouseButton.y));
      }

      if (event.mouseButton.button == sf::Mouse::Right) {
        spawnSpecialWeapon(m_Player);
      }
    }
  }
}


void Memor::sLifeSpan()
{
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
  if entity has no lifespan component, skip it
  if entity has > 0 lifespan, subtract 1
  if it has lifespan and is alive, scale alpha channel
  if lifespan is up, destroy the entity
   */
  }

}

void Memor::sRender() 
{
  // Clear window, render every entity, draw text and display
  m_Window.clear();

  for (auto e : m_Entities.getEntities()) {
    m_Window.draw(e->cShape->circle);
  }

  m_Window.draw(m_Text);
  m_Window.display();
}

void Memor::sEnemySpawner() 
{
  if (m_CurrentFrame - m_LastEnemySpawnTime > m_EnemyConfig.SP)
    spawnEnemy();
}

void Memor::sCollision() 
{
  // TODO
  // Implement all collisions using collision RADIUS

  for (auto &enemy : m_Entities.getEntities("enemy")) {
    float xPos = enemy->cTransform->m_Pos.x;
    float yPos = enemy->cTransform->m_Pos.y;
    float radius = enemy->cShape->circle.getRadius();

    // Collision / bouncing for entities that != player
    // X plane collision with walls
    if (xPos - radius < 0 || xPos + radius > m_Window.getSize().x) {
      enemy->cTransform->m_Velocity.x = -enemy->cTransform->m_Velocity.x;
    }

    // Y plane collision with walls
    if (yPos - radius < 0 || yPos + radius > m_Window.getSize().y) {
      enemy->cTransform->m_Velocity.y = -enemy->cTransform->m_Velocity.y;
    }

    // Player and enemy collision
    float distanceBeetweenCirclesSQ =
        (m_Player->cTransform->m_Pos.x - enemy->cTransform->m_Pos.x) *
            (m_Player->cTransform->m_Pos.x - enemy->cTransform->m_Pos.x) +
        (m_Player->cTransform->m_Pos.y - enemy->cTransform->m_Pos.y) *
            (m_Player->cTransform->m_Pos.y - enemy->cTransform->m_Pos.y);

    if (distanceBeetweenCirclesSQ <
        (enemy->cShape->circle.getRadius() +
         m_Player->cShape->circle.getRadius()) *
            (enemy->cShape->circle.getRadius() +
             m_Player->cShape->circle.getRadius())) {
      enemy->destroy();
      m_Player->destroy();
      spawnPlayer();
    }

    for (auto bullet : m_Entities.getEntities("bullet")) {
      float distanceBeetweenCirclesSQ =
          (bullet->cTransform->m_Pos.x - enemy->cTransform->m_Pos.x) *
              (bullet->cTransform->m_Pos.x - enemy->cTransform->m_Pos.x) +
          (bullet->cTransform->m_Pos.y - enemy->cTransform->m_Pos.y) *
              (bullet->cTransform->m_Pos.y - enemy->cTransform->m_Pos.y);

      if (distanceBeetweenCirclesSQ <
          (enemy->cShape->circle.getRadius() +
           bullet->cShape->circle.getRadius()) *
              (enemy->cShape->circle.getRadius() +
               bullet->cShape->circle.getRadius())) {
        enemy->destroy();
        bullet->destroy();
        spawnSmallEnemies(enemy);
        m_Score += enemy->cScore->m_Score;
      }
    }
  }

  // Smallenemies and player
  for (auto &smallEnemy : m_Entities.getEntities("smallEnemy")) {
    float xPos = smallEnemy->cTransform->m_Pos.x;
    float yPos = smallEnemy->cTransform->m_Pos.y;
    float radius = smallEnemy->cShape->circle.getRadius();

    float distanceBeetweenCirclesSQ =
        (m_Player->cTransform->m_Pos.x - smallEnemy->cTransform->m_Pos.x) *
            (m_Player->cTransform->m_Pos.x - smallEnemy->cTransform->m_Pos.x) +
        (m_Player->cTransform->m_Pos.y - smallEnemy->cTransform->m_Pos.y) *
            (m_Player->cTransform->m_Pos.y - smallEnemy->cTransform->m_Pos.y);

    if (distanceBeetweenCirclesSQ <
        (smallEnemy->cShape->circle.getRadius() +
         m_Player->cShape->circle.getRadius()) *
            (smallEnemy->cShape->circle.getRadius() +
             m_Player->cShape->circle.getRadius())) {
      smallEnemy->destroy();
      m_Player->destroy();
      spawnPlayer();
    }
  }


  //TODO Fix ugly and hard to read if statements 

  // Player xPos window bounds
  if (m_Player->cTransform->m_Pos.x - m_Player->cShape->circle.getRadius() < 0) {
    m_Player->cTransform->m_Pos.x = 0 + m_Player->cShape->circle.getRadius();
  } else if (m_Player->cTransform->m_Pos.x + m_Player->cShape->circle.getRadius() > m_Window.getSize().x) {
    m_Player->cTransform->m_Pos.x = m_Window.getSize().x - m_Player->cShape->circle.getRadius();
  }

  // Player yPos window bounds
  if (m_Player->cTransform->m_Pos.y - m_Player->cShape->circle.getRadius() < 0) {
    m_Player->cTransform->m_Pos.y = 0 + m_Player->cShape->circle.getRadius();
  } else if (m_Player->cTransform->m_Pos.y + m_Player->cShape->circle.getRadius() > m_Window.getSize().y) {
    m_Player->cTransform->m_Pos.y = m_Window.getSize().y - m_Player->cShape->circle.getRadius();
  }
}

void Memor::spawnPlayer() 
{
  auto entity = m_Entities.addEntity("player");

  // CShape(float radius, int points, const sf::Color& fillColor, const sf::Color& outlineColor, float outlineThickness)

  //Creating the components for player entity

  entity->cTransform = std::make_shared<CTransform>(math::vec2(m_Window.getSize().x / 2.0f, m_Window.getSize().y / 2.0f), math::vec2(1.0f, 1.0f), 0.0f);

  entity->cCollision = std::make_shared<CCollision>(m_PlayerConfig.CR);

  entity->cShape = std::make_shared<CShape>(
      m_PlayerConfig.SR, m_PlayerConfig.V,
      sf::Color(m_PlayerConfig.FR, m_PlayerConfig.FG, m_PlayerConfig.FG),
      sf::Color(m_PlayerConfig.OR, m_PlayerConfig.OG, m_PlayerConfig.OG),
      m_PlayerConfig.OT);

  entity->cInput = std::make_shared<CInput>();

  m_Player = entity;
}

void Memor::spawnEnemy() {
  // Enemy 32 32 3 3 255 255 255 2 3 8 90 60  // SR CR SMIN SMAX OR OG OB OT VMMIN VMAX L SP

  auto entity = m_Entities.addEntity("enemy");

  entity->cTransform = std::make_shared<CTransform>(
      // Spawn position
      math::vec2( 
          utils::generateRandomNumber(10 + m_EnemyConfig.SR, m_Window.getSize().x - (m_EnemyConfig.SR + 10)),
          utils::generateRandomNumber(10 + m_EnemyConfig.SR, m_Window.getSize().y - (m_EnemyConfig.SR + 10))),
      // Velocities
      math::vec2(
          utils::generateRandomNumber(m_EnemyConfig.SMIN, m_EnemyConfig.SMAX),
          utils::generateRandomNumber(m_EnemyConfig.SMIN, m_EnemyConfig.SMAX)),
      //Angle
      0.0f);

  entity->cCollision = std::make_shared<CCollision>(m_EnemyConfig.CR);

  entity->cShape = std::make_shared<CShape>(
      //Shape radius
      m_BulletConfig.SR,
      // Vertices
      utils::generateRandomNumber(m_EnemyConfig.VMIN, m_EnemyConfig.VMAX),
      // Fill color randomised
      sf::Color(utils::generateRandomNumber(0, 255),
                utils::generateRandomNumber(0, 255),
                utils::generateRandomNumber(0, 255)),
      // Outline color
      sf::Color(m_EnemyConfig.OR, m_EnemyConfig.OG, m_EnemyConfig.OB),
      // Outline thickness
      m_EnemyConfig.OT);

  entity->cScore =
      std::make_shared<CScore>(entity->cShape->circle.getPointCount() * 100);

  m_LastEnemySpawnTime = m_CurrentFrame;
}

void Memor::spawnSmallEnemies(std::shared_ptr<Entity> e) {
  // TODO make small enemies spread sides/360 degress
  int sides = e->cShape->circle.getPointCount();
  float theta = 360.0f / sides;

  for (int i = 0; i < sides; i++) {
    auto entity = m_Entities.addEntity("smallEnemy");

    float angle = i * theta;
    float radians = angle * 3.14159f / 180.0f;

    float xPos = e->cTransform->m_Pos.x +
                 e->cShape->circle.getRadius() * std::cos(radians);
    float yPos = e->cTransform->m_Pos.y +
                 e->cShape->circle.getRadius() * std::sin(radians);

    entity->cTransform = std::make_shared<CTransform>(
        math::vec2(xPos, yPos),
        math::vec2(std::cos(radians), std::sin(radians)), radians);


    entity->cLifespan = std::make_shared<CLifespan>(100);

    entity->cShape = 
      std::make_shared<CShape>(e->cShape->circle.getRadius() / 2, sides,
      e->cShape->circle.getFillColor(),
      e->cShape->circle.getOutlineColor(), 4.0f);

    entity->cShape->circle.setRotation(radians);

    entity->cScore = std::make_shared<CScore>(
        (entity->cShape->circle.getPointCount() * 100) * 2);
  }
}

void Memor::spawnBullet(std::shared_ptr<Entity> e, const math::vec2 &target) {
  auto bullet = m_Entities.addEntity("bullet");

  math::vec2 direction = target - m_Player->cTransform->m_Pos;

  float length =
      std::sqrt(direction.x * direction.x + direction.y * direction.y);
  direction.x /= length;
  direction.y /= length;

  direction.x *= m_BulletConfig.S;
  direction.y *= m_BulletConfig.S;

  bullet->cTransform = std::make_shared<CTransform>(m_Player->cTransform->m_Pos, direction, 0);

  bullet->cCollision = std::make_shared<CCollision>(m_BulletConfig.CR);

  bullet->cShape = std::make_shared<CShape>(
      m_BulletConfig.SR, m_BulletConfig.V,
      sf::Color(m_BulletConfig.FR, m_BulletConfig.FG, m_BulletConfig.FG),
      sf::Color(m_BulletConfig.OR, m_BulletConfig.OG, m_BulletConfig.OG), 2);

  bullet->cLifespan = std::make_shared<CLifespan>(m_BulletConfig.L);
}


void Memor::spawnSpecialWeapon(std::shared_ptr<Entity> e) {
  if (m_SpecialCD.elapsed() > 5.0f) {
  for (int i = 0; i < 360; i += 30) {
      float angle = math::toRadians(static_cast<float>(i));  // Convert angle to radians
      float radius = 50.0f;  // Radius of the circle

      // Calculate the position of the bullet using trigonometry
      float x = m_Player->cTransform->m_Pos.x + radius * std::cos(angle);
      float y = m_Player->cTransform->m_Pos.y + radius * std::sin(angle);

      math::vec2 target = {x, y};
      spawnBullet(m_Player, target);
      m_SpecialCD.reset();
  }
}


}
