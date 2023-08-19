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

  m_GridSize.x = m_Memor->getWindow().getSize().x / 20.0f;
  m_GridSize.y = m_Memor->getWindow().getSize().y / 12.0f;

  if (!m_Font.loadFromFile("fonts/arial.ttf"))
    std::cout << "Could not load font" << std::endl;

  m_GridText.setFont(m_Font);
  m_GridText.setCharacterSize(12);
  m_GridText.setFillColor(sf::Color::White);

  loadLevel(levelPath);

  return true;
}



void ScenePlay::loadLevel(std::string &filename) {
  // Load a new level, reset the entity manager, and spawn entities
  m_EntityManager = EntityManager();

  // Sample code for spawning entities
  spawnPlayer();

  std::ifstream configFile(filename);
  std::string line;
  while (std::getline(configFile, line)) {
    std::istringstream iss(line);
    std::string token;
    iss >> token;

    if (token == "Tile") {
      std::string type;
      int xPos;
      int yPos;
      iss >> type >> xPos >> yPos;

      auto tile = m_EntityManager.addEntity("tile");
      tile->addComponent<CAnimation>(m_Memor->getAssets().getAnimation(type), true);
      tile->getComponent<CAnimation>().m_Animation.setSize(m_GridSize);
      tile->addComponent<CTransform>(
          gridToMidPixel(math::vec2(xPos, yPos), tile));
      tile->addComponent<CBoundingBox>(
          tile->getComponent<CAnimation>().m_Animation.getSize());
    } else if (token == "Dec") {
      std::string type;
      int xPos;
      int yPos;
      iss >> type >> xPos >> yPos;

      auto dec = m_EntityManager.addEntity("Dec");
      dec->addComponent<CAnimation>(m_Memor->getAssets().getAnimation(type), true);
      dec->getComponent<CAnimation>().m_Animation.setSize(m_GridSize);
      dec->addComponent<CTransform>(gridToMidPixel(math::vec2(xPos, yPos), dec));


    }
  }
  configFile.close();
}



void ScenePlay::spawnPlayer() {
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

void ScenePlay::spawnBullet(std::shared_ptr<Entity> entity) {
  // Spawn a bullet entity at the given position, shooting at the direction the player is facing
  auto bullet = m_EntityManager.addEntity("bullet");
  int bulletSpeed = 10; // TODO: Read from config
  math::vec2 dir = math::vec2(-(m_Player->getComponent<CTransform>().m_Scale.x * bulletSpeed), 0); // Getting direction of bullet from where the player is facing
  bullet->addComponent<CLifespan>(100);
  bullet->addComponent<CShape>(2.0f, 8, sf::Color::White, sf::Color::White, 1.0f);
  bullet->addComponent<CTransform>(entity->getComponent<CTransform>().m_Pos, dir, math::vec2(0, 0));
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
}

void ScenePlay::sPlayerState() 
{
  // Update the player's state based on its position and movement
  auto &transform = m_Player->getComponent<CTransform>();
  auto &state = m_Player->getComponent<CState>();

  if       (!state.m_IsJumping && transform.m_Pos == transform.m_PrevPos)                                                  { state.m_State = "Standing"; } 
  else if (!state.m_IsJumping && transform.m_Pos.x != transform.m_PrevPos.x && transform.m_Pos.y == transform.m_PrevPos.y) { state.m_State = "Running"; } 
  else if (transform.m_Pos.y < transform.m_PrevPos.y)                                                                      {state.m_State = "Up"; } 
  else if (transform.m_Pos.y > transform.m_PrevPos.y)                                                                      { state.m_State = "Down"; }
}

void ScenePlay::sMovement() 
{
  // If the player's state is "up" or "down", maintain the vertical velocity and set horizontal velocity to zero
  if (m_Player->getComponent<CState>().m_State == "Up" || m_Player->getComponent<CState>().m_State == "Down") 
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
      e->getComponent<CTransform>().m_Velocity.y +=
      e->getComponent<CGravity>().m_Gravity;
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
  for (auto &e : m_EntityManager.getEntities()) {
    if (e->hasComponent<CLifespan>()) 
    {
      e->getComponent<CLifespan>().m_Remaining--;

      if (e->getComponent<CLifespan>().m_Remaining <= 0) 
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
    if (e->getTag() == "tile" || e->getTag() == "brick" || e->getTag() == "ground") 
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
        }

        // If the collision was with a brick and from below, destroy the brick and spawn a coin
        if (e->getComponent<CAnimation>().m_Animation.getName() == "Brick" && mtv.y > 0) 
        {
          auto coin = m_EntityManager.addEntity("coin");
          coin->addComponent<CAnimation>(m_Memor->getAssets().getAnimation("Coin"), true);
          coin->addComponent<CTransform>(math::vec2(e->getComponent<CTransform>().m_Pos.x , e->getComponent<CTransform>().m_Pos.y - e->getComponent<CBoundingBox>().m_Size.y));
          m_EntityManager.destroyEntity(e);
          continue;
        }
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
    else if (action.getName() == "SHOOT")               { spawnBullet(m_Player); m_Player->getComponent<CState>().m_State = "Shoot";
    }
  } 

  else if (action.getType() == "END") 

  {
    if      (action.getName() == "UP")                 { m_Player->getComponent<CInput>().up = false; m_Player->getComponent<CState>().m_JumpTimer = 6.0f; } 
    else if (action.getName() == "LEFT")               { m_Player->getComponent<CInput>().left = false; } 
    else if (action.getName() == "RIGHT")              { m_Player->getComponent<CInput>().right = false; }
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
    for (auto e : m_EntityManager.getEntities()) 
    {
      auto &transform = e->getComponent<CTransform>();
      if (e->hasComponent<CAnimation>() && e->getTag() != "player") 
      {
        auto &animation = e->getComponent<CAnimation>().m_Animation;

        animation.getSprite().setRotation(transform.m_Angle);
        animation.getSprite().setPosition(transform.m_Pos.x, transform.m_Pos.y);
        animation.getSprite().setScale(transform.m_Scale.x, transform.m_Scale.y);

        m_Memor->getWindow().draw(animation.getSprite());
      }
      if (e->hasComponent<CShape>()) 
      {
        m_Memor->getWindow().draw(e->getComponent<CShape>().circle);
      }
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

        m_GridText.setString("(" + std::to_string(xTile) + ", " + std::to_string(yTile) + ")");
        m_GridText.setPosition(x, y);

        yTile++;
        m_Memor->getWindow().draw(m_GridText);
      }
      xTile++;
    }

  }
  m_Memor->getWindow().display();
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
