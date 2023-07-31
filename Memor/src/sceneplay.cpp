#include "sceneplay.hpp"
#include "components/cboundbox.hpp"
#include "components/cinput.hpp"
#include "components/clifespan.hpp"
#include "components/cshape.hpp"
#include "components/ctransform.hpp"
#include "physics/physics.hpp"
#include "memor.hpp"
#include <sstream>



#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <string>

ScenePlay::ScenePlay(MemorGame* gameEngine, const std::string& levelPath)
: 
Scene(gameEngine),
m_LevelPath(levelPath)
{
  init(m_LevelPath);
}

bool ScenePlay::init(const std::string& levelPath)
{
  registerAction(sf::Keyboard::P, "PAUSE");
  registerAction(sf::Keyboard::Escape, "QUIT");
  registerAction(sf::Keyboard::T, "TOGGLE_TEXTURE");
  registerAction(sf::Keyboard::C, "TOGGLE_COLLISION");
  registerAction(sf::Keyboard::G, "TOGGLE_GRID");


  registerAction(sf::Keyboard::W, "UP");
  registerAction(sf::Keyboard::Up, "UP");
  registerAction(sf::Keyboard::S, "DOWN");
  registerAction(sf::Keyboard::Down, "DOWN");
  registerAction(sf::Keyboard::A, "LEFT");
  registerAction(sf::Keyboard::Left, "LEFT");
  registerAction(sf::Keyboard::D, "RIGHT");
  registerAction(sf::Keyboard::D, "RIGHT");
  registerAction(sf::Keyboard::Space, "SHOOT");

  //TODO Register all other gameplay Actions
  
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

math::vec2 ScenePlay::gridToMidPixel(math::vec2 gridPos, std::shared_ptr<Entity> entity)
{
  //TODO This method takes in a grid (x, y) position and an entity
  //Return a Vec2 indicitaing where the CENTER position of the entity should be
  //You must use the Entitys animation size to position it correctly
  //The size of the grid width and height is stored in m_Gridsize.x and m_GridSize.y
  //The bottom-left corner of the Animation should align with the bottom left of the grid cell


  math::vec2 result;

  if (!entity->hasComponent<CAnimation>()) return math::vec2(0, 0);

  result = gridToPixel(gridPos);
  result.y += m_GridSize.y;

  math::vec2 entityPos = entity->getComponent<CAnimation>().m_Animation.getSize();

  result.x += entityPos.x / 2.0f;
  result.y -= entityPos.y / 2.0f;

  return result;
}

void ScenePlay::loadLevel(const std::string& filename)
{
  // Reset entity when we load a new level
  m_EntityManager = EntityManager();

  //TODO read in level file and add appropiate entities
  //use the PlayerConfig strut m_PlayerConfig to store player properties
  //this struct is defined at the top of sceneplay.hpp
  
  //BELOW IS SAMPLE CODE

  spawnPlayer();


  //sample entities
  auto question = m_EntityManager.addEntity("tile");
  //IMPORTANT always add CAnimation component first so gridToMidPixel works correctly
  question->addComponent<CAnimation>(m_Memor->getAssets().getAnimation("Question1"), true);
  question->getComponent<CAnimation>().m_Animation.setSize(m_GridSize);
  question->addComponent<CTransform>(gridToMidPixel(math::vec2(1, 5), question));
  question->addComponent<CBoundingBox>(question->getComponent<CAnimation>().m_Animation.getSize());


  // auto brick = m_EntityManager.addEntity("tile");
  // //IMPORTANT always add CAnimation component first so gridToMidPixel works correctly
  // brick->addComponent<CAnimation>(m_Memor->getAssets().getAnimation("Brick"), true);
  // brick->getComponent<CAnimation>().m_Animation.setSize(m_GridSize);
  // brick->addComponent<CTransform>(gridToMidPixel(math::vec2(5, 4), brick));
  // brick->addComponent<CBoundingBox>(brick->getComponent<CAnimation>().m_Animation.getSize());


}

math::vec2 ScenePlay::gridToPixel(math::vec2 gridPos)
{
  return math::vec2(gridPos.x * m_GridSize.x, gridPos.y * m_GridSize.y);
}


void ScenePlay::spawnPlayer()
{
  m_Player = m_EntityManager.addEntity("player");
  m_Player->addComponent<CAnimation>(m_Memor->getAssets().getAnimation("Shoot"), true);
  m_Player->getComponent<CAnimation>().m_Animation.setSize(math::vec2(m_GridSize.x / 2.0f, m_GridSize.y / 2.0f));
  m_Player->addComponent<CTransform>(gridToMidPixel(math::vec2(10, 5), m_Player));
  m_Player->addComponent<CBoundingBox>(m_Player->getComponent<CAnimation>().m_Animation.getSize());
  m_Player->addComponent<CInput>();

  //TODO add rest of components to player

}


void ScenePlay::spawnBullet(std::shared_ptr<Entity> entity)
{
  //TODO spawn bullet at given and going in direction it is facing
  auto bullet = m_EntityManager.addEntity("bullet");
  int bulletSpeed = 10; // TODO READ FROM CONFIG
  math::vec2 dir = math::vec2(-(m_Player->getComponent<CTransform>().m_Scale.x * bulletSpeed), 0);


    // CShape(float radius, int points, const sf::Color& fillColor, const sf::Color& outlineColor, float outlineThickness) 

  bullet->addComponent<CLifespan>(100);
  bullet->addComponent<CShape>(2.0f, 8, sf::Color::White, sf::Color::White, 1.0f);
  bullet->addComponent<CTransform>(entity->getComponent<CTransform>().m_Pos, dir, math::vec2(0, 0));





}

void ScenePlay::update()
{
  //TODO add pause 

  m_EntityManager.update();

  sMovement();
  sLifespan();
  sCollision();
  sAnimation();
  sRender();
}

void ScenePlay::sMovement()
{
  m_Player->getComponent<CTransform>().m_Velocity = { 0.0f, 0.0f };

  if (m_Player->getComponent<CInput>().up)    { m_Player->getComponent<CTransform>().m_Velocity.y = -5; }
  if (m_Player->getComponent<CInput>().down)  { m_Player->getComponent<CTransform>().m_Velocity.y =  5; }
  if (m_Player->getComponent<CInput>().left)  { m_Player->getComponent<CTransform>().m_Velocity.x = -5; m_Player->getComponent<CTransform>().m_Scale.x =  1; }
  if (m_Player->getComponent<CInput>().right) { m_Player->getComponent<CTransform>().m_Velocity.x =  5; m_Player->getComponent<CTransform>().m_Scale.x = -1; }

  for (auto& e : m_EntityManager.getEntities())
  {
    e->getComponent<CTransform>().m_Pos += e->getComponent<CTransform>().m_Velocity;

  if (e->hasComponent<CShape>()) {
    e->getComponent<CShape>().circle.setPosition(e->getComponent<CTransform>().m_Pos.x, e->getComponent<CTransform>().m_Pos.y);
  }
  }

  /*TODO

  Implement player movement based on its CInput component
  Implement gravity effect on player
  Implement the maximum player speed in both x and y direction
  Setting entity scale.x to 1 / -1 decides it direction


  */

}

void ScenePlay::sLifespan()
{
  //TODO check lifespan of entity and destroy if over
  for (auto& e : m_EntityManager.getEntities()) {
    if (e->hasComponent<CLifespan>()) {
      e->getComponent<CLifespan>().m_Remaining--;
      if (e->getComponent<CLifespan>().m_Remaining <= 0) {
        m_EntityManager.destroyEntity(e);
      }
    }
  }
}

void ScenePlay::sCollision()
{
  //REMEMBER: 
  //
  //SFML's (0, 0) position is top left corner
  // Jumping will decrease Y value 
  // gravity will have positive y value
  // Something Below something else will have a greater Y value and opposite
  //
  //Implement getOverLap and use it here
  //Implement bullet / tile collision, destroy if brick
  //Implement tile - player collision and resolution
  //Update CState component to store if it is on the ground or not
  //Check if player has fallen down a hole
  //Dont let player walk off the left side of map

  for (auto& e : m_EntityManager.getEntities()) {

    if (e->getTag() != "player") {
      math::vec2 overlap = physics::GetOverlap(e, m_Player);
      // std::cout << overlap << std::endl;
    }
    

  }
}

void ScenePlay::sDoAction(const Action& action)
{
  if (action.getType() == "START")
  {
    if      (action.getName() == "TOGGLE_TEXTURE")      { m_DrawTextures = !m_DrawTextures; }
    else if (action.getName() == "TOGGLE_COLLISION")    { m_DrawCollision = !m_DrawCollision; }
    else if (action.getName() == "TOGGLE_GRID")         { m_DrawGrid = !m_DrawGrid; }
    else if (action.getName() == "PAUSE")               { togglePause(); }
    else if (action.getName() == "QUIT")                { onEnd(); }


    else if (action.getName() == "UP")                  {  m_Player->getComponent<CInput>().up = true; }
    else if (action.getName() == "DOWN")                {  m_Player->getComponent<CInput>().down = true; }
    else if (action.getName() == "LEFT")                {  m_Player->getComponent<CInput>().left = true; }
    else if (action.getName() == "RIGHT")               {  m_Player->getComponent<CInput>().right = true; }

    else if (action.getName() == "SHOOT")               {  spawnBullet(m_Player); }
  } 
  else if (action.getType() == "END")
  {
    if      (action.getName() == "UP")                  {  m_Player->getComponent<CInput>().up = false; }
    else if (action.getName() == "DOWN")                {  m_Player->getComponent<CInput>().down = false; }
    else if (action.getName() == "LEFT")                {  m_Player->getComponent<CInput>().left = false; }
    else if (action.getName() == "RIGHT")               {  m_Player->getComponent<CInput>().right = false; }
 
  }
}

void ScenePlay::sAnimation()
{
}


void ScenePlay::sRender()
{
  // Changing background color if game is paused
  if (!m_Paused) { m_Memor->getWindow().clear(sf::Color(100, 100, 255)); }
  else { m_Memor->getWindow().clear(sf::Color(50, 50, 150)); }

  // Setting viewport to be centered on the player when moving right
  auto& pPos = m_Player->getComponent<CTransform>().m_Pos;
  float windowCenterX = std::max(m_Memor->getWindow().getSize().x / 2.0f, pPos.x);
  sf::View view = m_Memor->getWindow().getView();
  view.setCenter(windowCenterX, m_Memor->getWindow().getSize().y - view.getCenter().y);
  m_Memor->getWindow().setView(view);

  if (m_DrawTextures) 
  {
    for (auto e : m_EntityManager.getEntities()) {
      auto& transform = e->getComponent<CTransform>();
      if (e->hasComponent<CAnimation>()) {
        auto& animation = e->getComponent<CAnimation>().m_Animation;
        animation.getSprite().setRotation(transform.m_Angle);
        animation.getSprite().setPosition(transform.m_Pos.x, transform.m_Pos.y);
        animation.getSprite().setScale(transform.m_Scale.x, transform.m_Scale.y);

        m_Memor->getWindow().draw(animation.getSprite());

      }
        if (e->hasComponent<CShape>()) {
          m_Memor->getWindow().draw(e->getComponent<CShape>().circle);
      }
    }
  }

  if (m_DrawCollision)
  {
    for (auto e : m_EntityManager.getEntities())
    {
      if (e->hasComponent<CBoundingBox>())
      {
        auto& box = e->getComponent<CBoundingBox>();
        auto& transform = e->getComponent<CTransform>();
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(box.m_Size.x -1, box.m_Size.y -1));
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
  if (playerX < m_Memor->getWindow().getSize().x / 2.0f) {  playerX = m_Memor->getWindow().getSize().x / 2.0f; }
  float windowWidth = m_Memor->getWindow().getSize().x;
  float leftX = 0.0f;
  float rightX = playerX + windowWidth / 2.0f;

  int xTile = 0;
  int yTile = 0;

  for (float x = leftX; x < rightX; x += m_GridSize.x)
  {
    drawLine(math::vec2(x, 0), math::vec2(x, m_Memor->getWindow().getSize().y));
    yTile = 0;
    for (float y = 0; y < m_Memor->getWindow().getSize().y; y += m_GridSize.y)
    {
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

void ScenePlay::togglePause()
{
  m_Paused = !m_Paused;
}



void ScenePlay::onEnd()
{
}

void ScenePlay::drawLine(const math::vec2& v1, const math::vec2& v2 ) 
{
  sf::Vertex line[] =
  {
    sf::Vertex(sf::Vector2f(v1.x, v1.y)),
    sf::Vertex(sf::Vector2f(v2.x, v2.y))
  };

  m_Memor->getWindow().draw(line, 2, sf::Lines);
}
