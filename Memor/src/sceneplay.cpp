#include "sceneplay.hpp"
#include "memor.hpp"

#include <SFML/Graphics/Font.hpp>
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

  if (!m_Font.loadFromFile("fonts/arial.ttf"))
  {
    std::cout << "Font not found!" << std::endl; 
    return false;
  }

  m_GridText.setFont(m_Font);
  m_GridText.setFillColor(sf::Color::White);

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
  //
  //BELOW IS SAMPLE CODE

  spawnPlayer();


  //sample entities
  auto brick = m_EntityManager.addEntity("tile");
  //IMPORTANT always add CAnimation component first so gridToMidPixel works correctly
  brick->addComponent<CAnimation>(m_Memor->getAssets().getAnimation("Brick"), true);
  brick->addComponent<CTransform>(math::vec2(96, 480));
  //Final code will position the entity with the grid x, y positio read from file
  // brick->addComponent<CTransform>(gridToMidPixel(gridX, gridY, brick));
  
  if (brick->getComponent<CAnimation>().m_Animation.getName() == "Brick")
  {
    std::cout << "Tile is Brick" << std::endl;
  }

  auto block = m_EntityManager.addEntity("tile");
  block->addComponent<CAnimation>(m_Memor->getAssets().getAnimation("Block"), true);
  block->addComponent<CTransform>(math::vec2(224, 480));
  // add a bounding box, shows up when toggling collision vision
  block->addComponent<CBoundingBox>(m_Memor->getAssets().getAnimation("Block").getSize());

  auto question = m_EntityManager.addEntity("tile");
  question->addComponent<CAnimation>(m_Memor->getAssets().getAnimation("Question"), true);
  question->addComponent<CTransform>(math::vec2(352, 480));

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
  //TODO Complete Animation class first

}


void ScenePlay::sRender()
{

  m_Memor->getWindow().clear();
  m_GridText.setString("Test");
  m_GridText.setPosition(m_Memor->getWindow().getSize().x / 2.0f, m_Memor->getWindow().getSize().y / 2.0f);
  m_Memor->getWindow().draw(m_GridText);
  m_Memor->getWindow().display();

}

void ScenePlay::togglePause()
{
  m_Paused = !m_Paused;
}



void ScenePlay::onEnd()
{

}
