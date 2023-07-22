#pragma once

#include "entity/entitymanager.hpp"
#include <unordered_map>

class MemorGame;

class Scene {

public:
  //Methods
  Scene(MemorGame * game);
  virtual void update() = 0;
  virtual void sDoAction() = 0;
  virtual void sRender() = 0;

  void simulate(int val); //TODO change val


  void doAction();
  void registerAction(sf::Keyboard::Key key, std::string actionName);



public:
  //Variables



private:
  //Methods

protected:
  void togglePause();
  void endScene();



protected:
  //Variables
  MemorGame* m_Memor;
  EntityManager m_Entities;
  int m_currentFrame;
  bool m_Paused = false;
  bool hasEnded = false;
  std::unordered_map<int, std::string> m_ActionMap;



};
