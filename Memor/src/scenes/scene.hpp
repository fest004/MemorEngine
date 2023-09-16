#pragma once

#include "../entity/ecs.hpp"
#include <map>
#include "../action.hpp"

class MemorGame;

class Scene {

public:
  //Methods
  Scene(MemorGame * game);
  virtual void update() = 0;
  virtual void sDoAction(const Action& action) = 0;
  virtual void sRender() = 0;

  void simulate(int val); //TODO change val


  void registerAction(sf::Keyboard::Key key, std::string actionName);

  const std::map<int, std::string>& getActionMap() const;



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
  EntityManager m_EntityManager;
  int m_currentFrame;
  bool m_Paused = false;
  bool m_HasEnded = false;
  std::map<int, std::string> m_ActionMap;



};
