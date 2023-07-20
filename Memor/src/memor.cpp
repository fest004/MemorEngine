// A3 WORK


#include "memor.hpp"
#include "components/ctransform.hpp"
#include "entity/entitymanager.hpp"
#include "math/vec2.hpp"
#include "utils/generaterandom.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>

Memor::Memor(const std::string &filepath) { init(filepath); }

bool Memor::init(std::string path) {
  m_Window.create(sf::VideoMode(800, 600), "Memor");

  return true;
}

void Memor::Run() {
  // TODO Add pause functionality

  while (m_Running) {
    if (!m_Paused) {


    // m_Entities.update();
    update();
    // sEnemySpawner();
    // sMovement();
    sCollision();
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

      }

      if (event.mouseButton.button == sf::Mouse::Right) {
      }
    }
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
}

void Memor::sCollision() 
{
}


void Memor::spawnPlayer() 
{

}

void Memor::spawnEnemy() {
}

void Memor::spawnBullet(std::shared_ptr<Entity> e, const math::vec2 &target) {
}


