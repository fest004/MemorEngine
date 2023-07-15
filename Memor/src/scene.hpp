#pragma once


#include "memor.hpp"
#include "entity/entitymanager.hpp"

class Scene {

public:
  //Methods
  virtual void update() = 0;
  virtual void sDoAction() = 0;
  virtual void sRender() = 0;

  void simulate(int val); //TODO change val


  void doAction();
  void registerAction();



public:
  //Variables



private:
  //Methods




private:
  //Variables
  Memor* m_Memor;
  EntityManager m_Entities;
  int m_currentFrame;
  bool m_Paused = false;
  bool hasEnded = false;
  std::unordered_map<int, std::string> m_ActionMap;



};
