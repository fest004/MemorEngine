#include "sceneplay.hpp"
#include "components/cboundbox.hpp"
#include "components/cgravity.hpp"
#include "components/cinput.hpp"
#include "components/clifespan.hpp"
#include "components/cshape.hpp"
#include "components/ctransform.hpp"
#include "memor.hpp"
#include "physics/physics.hpp"
#include <fstream>
#include <sstream>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <ios>
#include <iostream>
#include <string>

ScenePlay::ScenePlay(MemorGame *gameEngine, const std::string &levelPath)
: Scene(gameEngine), m_LevelPath(levelPath) 
{
  init(m_LevelPath);
}

bool ScenePlay::init(std::string &levelPath) 
{
  // Actions that players can take
  registerAction(sf::Keyboard::P, "PAUSE");
  registerAction(sf::Keyboard::Escape, "QUIT");
  registerAction(sf::Keyboard::T, "TOGGLE_TEXTURE");
  registerAction(sf::Keyboard::C, "TOGGLE_COLLISION");
  registerAction(sf::Keyboard::G, "TOGGLE_GRID");

  registerAction(sf::Keyboard::W, "UP");
  registerAction(sf::Keyboard::Up, "UP");
  registerAction(sf::Keyboard::A, "LEFT");
  registerAction(sf::Keyboard::Left, "LEFT");
  registerAction(sf::Keyboard::D, "RIGHT");
  registerAction(sf::Keyboard::Right, "RIGHT");
  registerAction(sf::Keyboard::Space, "SHOOT");

  m_GridSize.x = m_Memor->getWindow().getSize().x / 20.0f;
  m_GridSize.y = m_Memor->getWindow().getSize().y / 12.0f;

  if (!m_Font.loadFromFile("fonts/arial.ttf"))
    std::cout << "Could not load font" << std::endl;

  m_Text.setFont(m_Font);
  m_Text.setCharacterSize(12);
  m_Text.setFillColor(sf::Color::White);

  loadLevel(levelPath);

  return true;
}



void ScenePlay::loadLevel(std::string &filename) {
  // Load a new level, reset the entity manager, and spawn entities
  m_EntityManager = EntityManager();

  // Sample code for spawning entities
  auto score = m_EntityManager.addEntity("Dec");
  score->addComponent<CAnimation>(m_Memor->getAssets().getAnimation("Coin"), true);
  score->addComponent<CTransform>(math::vec2(30, 30));

  spawnPlayer();
  spawnGoomba(math::vec2(5, 10));
  m_BulletTimer.reset();

  std::ifstream configFile(filename);
  std::string line;
  while (std::getline(configFile, line)) 
  {
    std::istringstream iss(line);
    std::string token;
    iss >> token;

    if (token == "Tile") 
    {
      std::string type;
      int xPos;
      int yPos;
      iss >> type >> xPos >> yPos;

      auto tile = m_EntityManager.addEntity("Tile");

      tile->addComponent<CAnimation>(m_Memor->getAssets().getAnimation(type), true);
      tile->getComponent<CAnimation>().m_Animation.setSize(m_GridSize);
      tile->addComponent<CTransform>(gridToMidPixel(math::vec2(xPos, yPos), tile));
      tile->addComponent<CBoundingBox>(tile->getComponent<CAnimation>().m_Animation.getSize());
    } 
    else if (token == "Dec") 
    {
      std::string type;
      int xPos;
      int yPos;
      iss >> type >> xPos >> yPos;

      auto dec = m_EntityManager.addEntity("Dec");
      dec->addComponent<CAnimation>(m_Memor->getAssets().getAnimation(type), true);
      dec->getComponent<CAnimation>().m_Animation.setSize(m_GridSize);
      dec->addComponent<CTransform>(gridToMidPixel(math::vec2(xPos, yPos), dec));
    }
    else if (token == "Goomba")
    {
    int xPos;
    int yPos;
    iss >> xPos >> yPos;

    spawnGoomba(math::vec2(xPos, yPos));
    }
  }
  configFile.close();
}



void ScenePlay::spawnPlayer() 
{
  // Spawn the player entity with specific components
  m_Player = m_EntityManager.addEntity("player");
  m_Player->addComponent<CAnimation>(m_Memor->getAssets().getAnimation("Shoot"), true);
  m_Player->getComponent<CAnimation>().m_Animation.setSize(math::vec2(m_GridSize.x / 2.0f, m_GridSize.y / 2.0f));
  m_Player->addComponent<CTransform>(gridToMidPixel(math::vec2(3, 10), m_Player));
  m_Player->addComponent<CBoundingBox>(
  m_Player->getComponent<CAnimation>().m_Animation.getSize());
  m_Player->addComponent<CGravity>(1.0f);
  m_Player->addComponent<CState>();
  m_Player->addComponent<CInput>();

}

void ScenePlay::spawnGoomba(const math::vec2& pos)
{
   auto enemy = m_EntityManager.addEntity("enemy");
  enemy->addComponent<CAnimation>(m_Memor->getAssets().getAnimation("Goomba"), true);
  enemy->getComponent<CAnimation>().m_Animation.setSize(math::vec2(m_GridSize.x / 2.0f, m_GridSize.y / 2.0f));
  enemy->addComponent<CTransform>(gridToMidPixel(math::vec2(pos), enemy));
  enemy->getComponent<CTransform>().m_Velocity = math::vec2(1.0f, 5.0f);
  enemy->addComponent<CBoundingBox>(enemy->getComponent<CAnimation>().m_Animation.getSize());
  enemy->addComponent<CState>();

}



void ScenePlay::update() {
  // Update all subsystems
  m_EntityManager.update();
  sMovement();
  sLifespan();
  sCollision();
  sAnimation();
  sRender();
  sPlayerState();
  sScore();
}

void ScenePlay::sScore()
{
  m_Text.setString("");
}

void ScenePlay::sPlayerState() 
{
  // Update the player's state based on its position and movement
  auto &transform = m_Player->getComponent<CTransform>();
  auto &state = m_Player->getComponent<CState>();

  if       (!state.m_IsJumping && transform.m_Pos == transform.m_PrevPos)                                                  { state.m_State = "Standing"; } 
  else if (!state.m_IsJumping && transform.m_Pos.x != transform.m_PrevPos.x && transform.m_Pos.y == transform.m_PrevPos.y) { state.m_State = "Running";  } 
  else if (transform.m_Pos.y < transform.m_PrevPos.y)                                                                      { state.m_State = "Up";       } 
  else if (transform.m_Pos.y > transform.m_PrevPos.y)                                                                      { state.m_State = "Down";     }
  else                                                                                                                     { state.m_State = "Down";     }
}

void ScenePlay::sMovement() 
{
  // If the player's state is "up" or "down", maintain the vertical velocity and set horizontal velocity to zero
  if (m_Player->getComponent<CState>().m_State == "Up" || m_Player->getComponent<CState>().m_State == "Down" || m_Player->getComponent<CState>().m_State == "Shoot") 
  {
    m_Player->getComponent<CTransform>().m_Velocity = { 0.0f, m_Player->getComponent<CTransform>().m_Velocity.y };
  } 
  else 
  {
    m_Player->getComponent<CTransform>().m_Velocity = {0.0f, 0.0f};
  }

  // Check if the up key is pressed, the player isn't in "down" state, and hasn't jumped for more than 5 seconds
  if (m_Player->getComponent<CInput>().up && m_Player->getComponent<CState>().m_JumpTimer < 5.0f && m_Player->getComponent<CState>().m_State != "Down") 
  {
    m_Player->getComponent<CTransform>().m_Velocity.y = -10;
    m_Player->getComponent<CState>().m_JumpTimer += 0.2f;
  }

  // Check if the down, left, or right keys are pressed and update the player's velocity and scale accordingly
  // if (m_Player->getComponent<CInput>().down) { m_Player->getComponent<CTransform>().m_Velocity.y = 5; }
  if (m_Player->getComponent<CInput>().left) { m_Player->getComponent<CTransform>().m_Velocity.x = -5; m_Player->getComponent<CTransform>().m_Scale.x = 1; }
  if (m_Player->getComponent<CInput>().right) { m_Player->getComponent<CTransform>().m_Velocity.x = 5; m_Player->getComponent<CTransform>().m_Scale.x = -1; }

  // Iterate through all entities and update their positions and velocities based on their components
  for (auto &e : m_EntityManager.getEntities()) 
  {
    if (e->hasComponent<CGravity>()) 
    {
      e->getComponent<CTransform>().m_Velocity.y += e->getComponent<CGravity>().m_Gravity;
    }
    e->getComponent<CTransform>().m_PrevPos = e->getComponent<CTransform>().m_Pos;
    e->getComponent<CTransform>().m_Pos += e->getComponent<CTransform>().m_Velocity;

    if (e->hasComponent<CShape>()) 
    {
      e->getComponent<CShape>().circle.setPosition(e->getComponent<CTransform>().m_Pos.x, e->getComponent<CTransform>().m_Pos.y);
    }
  }
}

void ScenePlay::sLifespan() 
{
  // Iterate through all entities and check their lifespan component, destroy if the lifespan is over
  for (auto &e : m_EntityManager.getEntities()) 
  {
    if (e->hasComponent<CLifespan>()) 
    {
      e->getComponent<CLifespan>().m_Remaining--;

      if (e->getComponent<CLifespan>().m_Remaining <= 0) 
      {
        m_EntityManager.destroyEntity(e);
      }
    }

    // Destroying entites that has an animation that has ended
    if (e->hasComponent<CAnimation>())
    {
      if (e->getComponent<CAnimation>().m_Animation.hasEnded() && !e->getComponent<CAnimation>().m_Repeat) 
      {
        m_EntityManager.destroyEntity(e);
      }
    }
  }

  
}

void ScenePlay::sCollision() 
{
  // Player and tile collision
  for (auto &e : m_EntityManager.getEntities()) 
  {
    if (e->getTag() == "Tile" || e->getTag() == "brick" || e->getTag() == "ground") 
    {
      // Calculate the overlap between the player and the entity
      math::vec2 overlap = physics::GetOverlap(e, m_Player);

      // Check if there's an overlap
      if (overlap.x > 0 && overlap.y > 0) 
      {
        // Collision resolution is handled differently for an x overlap and y overlap, so check which one it is and apply according collision
        math::vec2 mtv;
        bool isVerticalCollision = overlap.y < overlap.x;
        if (isVerticalCollision) 
        {
          mtv = math::vec2(0, (m_Player->getComponent<CTransform>().m_Pos.y < e->getComponent<CTransform>().m_Pos.y) ? -overlap.y : overlap.y);
        } 
        else 
        {
          mtv = math::vec2((m_Player->getComponent<CTransform>().m_Pos.x < e->getComponent<CTransform>().m_Pos.x) ? -overlap.x : overlap.x, 0);
        }

        // Apply the MTV to the player to correct the collision
        m_Player->getComponent<CTransform>().m_Pos += mtv;

        // If the player collides on top of an entity, update the player's jumping state
        if (isVerticalCollision) 
        {
          // Determine the bottom of the players hitbox and the top of the entitys hitbox
          float playerBottom = m_Player->getComponent<CTransform>().m_Pos.y + m_Player->getComponent<CBoundingBox>().m_Size.y; 
          float entityTop = e->getComponent<CTransform>().m_Pos.y;

          // Check if the MTV is directing upward (indicating the player is landing on top)
          bool isLandingOnTop = (mtv.y < 0) && (playerBottom <= entityTop);

          if (isLandingOnTop) 
          {
            m_Player->getComponent<CState>().m_IsJumping = false;
            m_Player->getComponent<CState>().m_JumpTimer = 0.0f;
          } 
          else 
          {
            m_Player->getComponent<CTransform>().m_Velocity.y = 0;
            m_Player->getComponent<CState>().m_State = "Down";
          }

        } 
        // If the collision was with a brick and from below, destroy the brick and spawn a coin
        if (e->getComponent<CAnimation>().m_Animation.getName() == "Brick" && mtv.y > 0) 
        {
          m_EntityManager.destroyEntity(e);
          continue;
        }

        if (e->getComponent<CAnimation>().m_Animation.getName() == "Question" && mtv.y > 0) 
        {
          e->addComponent<CAnimation>(m_Memor->getAssets().getAnimation("QuestionHit"), true);
          auto coin = m_EntityManager.addEntity("Dec");
          coin->addComponent<CAnimation>(m_Memor->getAssets().getAnimation("Coin"), false);
          coin->addComponent<CTransform>(math::vec2(e->getComponent<CTransform>().m_Pos.x , e->getComponent<CTransform>().m_Pos.y - e->getComponent<CBoundingBox>().m_Size.y));
        }
      }

      for (auto& enemy : m_EntityManager.getEntities("enemy"))
      {

      math::vec2 overlap = physics::GetOverlap(e, enemy);

      // Check if there's an overlap
      if (overlap.x > 0 && overlap.y > 0) 
      {
        // Collision resolution is handled differently for an x overlap and y overlap, so check which one it is and apply according collision
        math::vec2 mtv;
        bool isVerticalCollision = overlap.y < overlap.x;
        if (isVerticalCollision) 
        {
          mtv = math::vec2(0, (enemy->getComponent<CTransform>().m_Pos.y < e->getComponent<CTransform>().m_Pos.y) ? -overlap.y : overlap.y);
        } 
        else 
        {
          if (overlap.y >= 58) {
              mtv = math::vec2((enemy->getComponent<CTransform>().m_Pos.x < e->getComponent<CTransform>().m_Pos.x) ? -overlap.x : overlap.x, 0);
              enemy->getComponent<CTransform>().m_Velocity.x = -(enemy->getComponent<CTransform>().m_Velocity.x);
          }
        }

        // Apply the MTV to the player to correct the collision
        enemy->getComponent<CTransform>().m_Pos += mtv;

        // If the player collides on top of an entity, update the player's jumping state
        if (isVerticalCollision) 
        {
          // Determine the bottom of the players hitbox and the top of the entitys hitbox
          float enemyBottom = enemy->getComponent<CTransform>().m_Pos.y + enemy->getComponent<CBoundingBox>().m_Size.y; 
          float entityTop = e->getComponent<CTransform>().m_Pos.y;

          // Check if the MTV is directing upward (indicating the player is landing on top)
          bool isLandingOnTop = (mtv.y < 0) && (enemyBottom <= entityTop);

          if (isLandingOnTop) 
          {
            enemy->getComponent<CState>().m_IsJumping = false;
          } 
          else 
          {
           enemy->getComponent<CState>().m_IsJumping = true;
          }
       } 
      }
    }
    }
  }
  //Make enemy diseappear if landing on top
    for (auto& enemy : m_EntityManager.getEntities("enemy")) 
    {
math::vec2 overlap = physics::GetOverlap(m_Player, enemy);

    // Check if there's an overlap
    if (overlap.x > 0 && overlap.y > 0) 
    {
        // Determine if it's a vertical collision
        bool isVerticalCollision = overlap.y < overlap.x;
      std::cout << overlap << std::endl;

        if (isVerticalCollision) 
        {
            // Determine which direction the collision is from
            math::vec2 mtv = math::vec2(0, (enemy->getComponent<CTransform>().m_Pos.y < m_Player->getComponent<CTransform>().m_Pos.y) ? -overlap.y : overlap.y);

            // Calculate the bottom of the player's hitbox and the top of the enemy's hitbox
            float playerBottom = m_Player->getComponent<CTransform>().m_Pos.y + m_Player->getComponent<CBoundingBox>().m_Size.y; 
            float enemyTop = enemy->getComponent<CTransform>().m_Pos.y;

          std::cout << mtv << std::endl;
            // Check if the MTV is directing upward (indicating the player is landing on top of the enemy)
          m_EntityManager.destroyEntity(enemy);
        }
        else 
        {
            std::cout << "Side" << std::endl;
        m_EntityManager.destroyEntity(m_Player);
        spawnPlayer();

            // If the player hits the enemy from the side, you might want to reduce the player's health, or change player's state, etc.
        }
    }
      
    }
}

void ScenePlay::sDoAction(const Action &action) 
{
  if (action.getType() == "START") 
  {
    if      (action.getName() == "TOGGLE_TEXTURE")      { m_DrawTextures = !m_DrawTextures; } 
    else if (action.getName() == "TOGGLE_COLLISION")    { m_DrawCollision = !m_DrawCollision; } 
    else if (action.getName() == "TOGGLE_GRID")         { m_DrawGrid = !m_DrawGrid; } 
    else if (action.getName() == "PAUSE")               { togglePause(); } 
    else if (action.getName() == "QUIT")                { onEnd(); }

    else if (action.getName() == "UP")                  { m_Player->getComponent<CInput>().up = true; m_Player->getComponent<CState>().m_IsJumping = true; } 
    else if (action.getName() == "LEFT")                { m_Player->getComponent<CInput>().left = true; } 
    else if (action.getName() == "RIGHT")               { m_Player->getComponent<CInput>().right = true; }
    else if (action.getName() == "SHOOT")               { m_Player->getComponent<CInput>().shoot = true; spawnBullet(m_Player);  }
  } 

  else if (action.getType() == "END") 

  {
    if      (action.getName() == "UP")                 { m_Player->getComponent<CInput>().up = false; m_Player->getComponent<CState>().m_JumpTimer = 6.0f; } 
    else if (action.getName() == "LEFT")               { m_Player->getComponent<CInput>().left = false; } 
    else if (action.getName() == "RIGHT")              { m_Player->getComponent<CInput>().right = false; }
    else if (action.getName() == "SHOOT")              { m_Player->getComponent<CInput>().shoot = false;  }
  }
}

void ScenePlay::sAnimation() 
{
  for (auto &e : m_EntityManager.getEntities()) 
  {
    if (e->getComponent<CAnimation>().has && e->getTag() != "player") 
      e->getComponent<CAnimation>().m_Animation.update();
  }

  m_Player->getComponent<CAnimation>().m_Animation.update();

  if (m_Player->getComponent<CAnimation>().m_Animation.getName() == m_Player->getComponent<CState>().m_State) 
    return;

  if      (m_Player->getComponent<CState>().m_State == "Up")       { m_Player->addComponent<CAnimation>(m_Memor->getAssets().getAnimation("Up"), true); } 
  else if (m_Player->getComponent<CState>().m_State == "Down")     { m_Player->addComponent<CAnimation>(m_Memor->getAssets().getAnimation("Down"), true); } 
  else if (m_Player->getComponent<CState>().m_State == "Standing") { m_Player->addComponent<CAnimation>(m_Memor->getAssets().getAnimation("Standing"), true); } 
  else if (m_Player->getComponent<CState>().m_State == "Running")  { m_Player->addComponent<CAnimation>(m_Memor->getAssets().getAnimation("Running"), true);} 
  else                                                             { m_Player->addComponent<CAnimation>(m_Memor->getAssets().getAnimation("Shoot"), true); }

}

void ScenePlay::sRender() 
{
  // Changing background color if game is paused
m_Paused ? m_Memor->getWindow().clear(sf::Color(50, 50, 150)) : m_Memor->getWindow().clear(sf::Color(100, 100, 255));

  // Setting viewport to be centered on the player when moving right
  auto &pPos = m_Player->getComponent<CTransform>().m_Pos;
  float windowCenterX = std::max(m_Memor->getWindow().getSize().x / 2.0f, pPos.x);
  sf::View view = m_Memor->getWindow().getView();
  view.setCenter(windowCenterX, m_Memor->getWindow().getSize().y - view.getCenter().y);
  m_Memor->getWindow().setView(view);

  if (m_DrawTextures) 
  {
    for (auto& e : m_EntityManager.getEntities("Dec"))
    {
      auto &animation = e->getComponent<CAnimation>().m_Animation;
      auto &transform = e->getComponent<CTransform>();

      animation.getSprite().setRotation(transform.m_Angle);
      animation.getSprite().setPosition(transform.m_Pos.x, transform.m_Pos.y);
      animation.getSprite().setScale(transform.m_Scale.x, transform.m_Scale.y);

      m_Memor->getWindow().draw(animation.getSprite());
    }

    for (auto& e : m_EntityManager.getEntities("Tile"))
    {
      auto &animation = e->getComponent<CAnimation>().m_Animation;
      auto &transform = e->getComponent<CTransform>();

      animation.getSprite().setRotation(transform.m_Angle);
      animation.getSprite().setPosition(transform.m_Pos.x, transform.m_Pos.y);
      animation.getSprite().setScale(transform.m_Scale.x, transform.m_Scale.y);

      m_Memor->getWindow().draw(animation.getSprite());
    }

    for (auto& e : m_EntityManager.getEntities("enemy"))
    {
      auto &animation = e->getComponent<CAnimation>().m_Animation;
      auto &transform = e->getComponent<CTransform>();

      animation.getSprite().setRotation(transform.m_Angle);
      animation.getSprite().setPosition(transform.m_Pos.x, transform.m_Pos.y);
      animation.getSprite().setScale(transform.m_Scale.x, transform.m_Scale.y);

      m_Memor->getWindow().draw(animation.getSprite());
    }

      auto &animation = m_Player->getComponent<CAnimation>().m_Animation;
      auto &transform = m_Player->getComponent<CTransform>();

      animation.getSprite().setRotation(transform.m_Angle);
      animation.getSprite().setPosition(transform.m_Pos.x, transform.m_Pos.y);
      animation.getSprite().setScale(transform.m_Scale.x, transform.m_Scale.y);

      m_Memor->getWindow().draw(animation.getSprite());

  }

  if (m_DrawCollision) 
  {
    for (auto e : m_EntityManager.getEntities()) 
    {
      if (e->hasComponent<CBoundingBox>()) 
      {
        auto &box = e->getComponent<CBoundingBox>();
        auto &transform = e->getComponent<CTransform>();
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(box.m_Size.x - 1, box.m_Size.y - 1));
        rect.setOrigin(sf::Vector2f(box.m_HalfSize.x, box.m_HalfSize.y));
        rect.setPosition(transform.m_Pos.x, transform.m_Pos.y);
        rect.setFillColor(sf::Color(0, 0, 0, 0));
        rect.setOutlineColor(sf::Color(255, 255, 255, 255));
        rect.setOutlineThickness(1);
        m_Memor->getWindow().draw(rect);
      }
    }
  }

  if (m_DrawGrid) 
  {
    float playerX = m_Player->getComponent<CTransform>().m_Pos.x;
    if (playerX < m_Memor->getWindow().getSize().x / 2.0f) 
    {
      playerX = m_Memor->getWindow().getSize().x / 2.0f;
    }

    float windowWidth = m_Memor->getWindow().getSize().x;

    float leftX = 0.0f;
    float rightX = playerX + windowWidth / 2.0f;
    int xTile = 0;
    int yTile = 0;

    for (float x = leftX; x < rightX; x += m_GridSize.x) 
    {
      drawLine(math::vec2(x, 0), math::vec2(x, m_Memor->getWindow().getSize().y));
      yTile = 0;

      for (float y = 0; y < m_Memor->getWindow().getSize().y; y += m_GridSize.y) {
        if (x == leftX) // Draw horizontal lines only once for each y
        {
          drawLine(math::vec2(leftX, y), math::vec2(rightX, y));
        }

        m_Text.setString("(" + std::to_string(xTile) + ", " + std::to_string(yTile) + ")");
        m_Text.setPosition(x, y);

        yTile++;
        m_Memor->getWindow().draw(m_Text);
      }
      xTile++;
    }

  }
  m_Memor->getWindow().display();
}

void ScenePlay::spawnBullet(std::shared_ptr<Entity> entity) 
{
  // Spawn a bullet entity at the given position, shooting at the direction the player is facing
  if (m_BulletTimer.elapsed() < m_BulletCD) return;

  m_Player->getComponent<CState>().m_State = "Shoot";    
  auto bullet = m_EntityManager.addEntity("bullet");
  int bulletSpeed = 10; // TODO: Read from config
  math::vec2 dir = math::vec2(-(m_Player->getComponent<CTransform>().m_Scale.x * bulletSpeed), 0); // Getting direction of bullet from where the player is facing
  bullet->addComponent<CLifespan>(100);
  bullet->addComponent<CShape>(2.0f, 8, sf::Color::White, sf::Color::White, 1.0f);
  bullet->addComponent<CTransform>(entity->getComponent<CTransform>().m_Pos, dir, math::vec2(0, 0));
  m_BulletTimer.reset();
}

void ScenePlay::togglePause() { m_Paused = !m_Paused; }

void ScenePlay::onEnd() {}

math::vec2 ScenePlay::gridToPixel(math::vec2 gridPos) 
{
  // Convert grid position to pixel coordinates
  return math::vec2(gridPos.x * m_GridSize.x, gridPos.y * m_GridSize.y);
}

math::vec2 ScenePlay::gridToMidPixel(math::vec2 gridPos, std::shared_ptr<Entity> entity) 
{
  // Calculate the center position of the given entity within the grid cell
  math::vec2 result;

  if (!entity->hasComponent<CAnimation>())
    return math::vec2(0, 0);

  result = gridToPixel(gridPos);
  result.y += m_GridSize.y;
  math::vec2 entityPos = entity->getComponent<CAnimation>().m_Animation.getSize();
  result.x += entityPos.x / 2.0f;
  result.y -= entityPos.y / 2.0f;
  return result;
}

void ScenePlay::drawLine(const math::vec2 &v1, const math::vec2 &v2) 
{
  sf::Vertex line[] = {sf::Vertex(sf::Vector2f(v1.x, v1.y)), sf::Vertex(sf::Vector2f(v2.x, v2.y))};

  m_Memor->getWindow().draw(line, 2, sf::Lines);
}
