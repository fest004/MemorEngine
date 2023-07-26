#include "sceneplay.hpp"
#include "components/cboundbox.hpp"
#include "memor.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

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

  //TODO Register all other gameplay Actions

  m_GridText.setCharacterSize(12);

  loadLevel(levelPath);

  return true;
}

math::vec2 ScenePlay::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
  //TODO This method takes in a grid (x, y) position and an entity
  //Return a Vec2 indicitaing where the CENTER position of the entity should be
  //You must use the Entitys animation size to position it correctly
  //The size of the grid width and height is stored in m_Gridsize.x and m_GridSize.y
  //The bottom-left corner of the Animation should align with the bottom left of the grid cell

  return math::vec2(0, 0);
}

void ScenePlay::loadLevel(const std::string& filename)
{
  // Reset entity when we load a new level
  m_EntityManager = EntityManager();

  //TODO read in level file and add appropiate entities
  //use the PlayerConfig strut m_PlayerConfig to store player properties
  //this struct is defined at the top of sceneplay.hpp
  
  //BELOW IS SAMPLE CODE

  // spawnPlayer();


  //sample entities
  auto brick = m_EntityManager.addEntity("tile");
  //IMPORTANT always add CAnimation component first so gridToMidPixel works correctly
  brick->addComponent<CAnimation>(m_Memor->getAssets().getAnimation("Question1"), true);
  brick->addComponent<CTransform>(math::vec2(96, 480));
  //Final code will position the entity with the grid x, y positio read from file
  // brick->addComponent<CTransform>(gridToMidPixel(gridX, gridY, brick));
  
  if (brick->getComponent<CAnimation>().m_Animation.getName() == "Question1")
  {
    std::cout << "Tile is Brick" << std::endl;
  }

  auto block = m_EntityManager.addEntity("tile");
  block->addComponent<CAnimation>(m_Memor->getAssets().getAnimation("Question1"), true);
  block->addComponent<CTransform>(math::vec2(224, 480));
  // add a bounding box, shows up when toggling collision vision
  block->addComponent<CBoundingBox>(m_Memor->getAssets().getAnimation("Question1").getSize());

  auto question = m_EntityManager.addEntity("tile");
  question->addComponent<CAnimation>(m_Memor->getAssets().getAnimation("Question1"), true);
  question->addComponent<CTransform>(math::vec2(352, 480));
  question->addComponent<CBoundingBox>(m_Memor->getAssets().getAnimation("Question1").getSize());
  

  // NOTE
  // Components are now returned as references rather than pointers
  //
}


void ScenePlay::spawnPlayer()
{
  m_Player = m_EntityManager.addEntity("player");
  m_Player->addComponent<CAnimation>(m_Memor->getAssets().getAnimation("Stand"), true);
  m_Player->addComponent<CTransform>(math::vec2(224, 352));
  m_Player->addComponent<CBoundingBox>(math::vec2(48, 48));

  //TODO add rest of components to player

}


void ScenePlay::spawnBullet(std::shared_ptr<Entity> entity)
{
  //TODO spawn bullet at given and going in direction it is facing
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
  //
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
  } 
  else if (action.getType() == "END")
  {

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

  /* Setting viewport to be centered on the player when moving right
  auto& pPos = m_Player->getComponent<CTransform>().m_pos;
  float windowCenterX = std::max(m_Memor->getWindow()->getSize().x / 2.0f, pPos.x);
  sf::View view = m_Memor->getWindow().getView();
  view.setCenter(windowCenterX, m_Memor->getWindow().getSize().y - view.getCenter().y);
  m_Memor->getWindow().setView(view);
  */

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

      if (m_DrawGrid)
      {
        float leftX = m_Memor->getWindow().getView().getCenter().x - m_Memor->getWindow().getSize().x / 2.0f;
        float rightX = leftX + m_Memor->getWindow().getSize().x + m_GridSize.x;
        float nextGridX = leftX - ((int)leftX % (int)m_GridSize.x);

        for (float x = nextGridX; x < rightX; x += m_GridSize.x)
        {
           // drawLine(math::vec2(x, 0), math::vec2(x, m_Memor->getWindow().getSize().y));
        }

        for (float y = 0; y < m_Memor->getWindow().getSize().y; y += m_GridSize.y)
        {
           // drawLine(math::vec2(y, 0), math::vec2(y, m_Memor->getWindow().getSize().x));
        }
      }


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
