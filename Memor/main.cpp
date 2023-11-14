// STD Headers
#include <SFML/Graphics/Color.hpp>
#include <iostream>

// SFML Headers
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>

// Memor headers
#include "src/memor.hpp"
#include "src/utils/fileread.h"

#include "temp/scenemenu.hpp"
#include "temp/scenemenu.cpp"

#include "src/memorlogger/log.hpp"
#include "src/memorlogger/logger.hpp"
int main() {


  //Config to be changed to A3 Config file
  MemorGame memor("temp/A2/config.txt");

  SceneMenu* sceneMenu = new SceneMenu(&memor);
  //memor.addInitialScene("MENUSCENE", std::make_shared<SceneMenu>(&memor));
  memor.run("MENUSCENE", std::make_shared<SceneMenu>(&memor));

  return 0;
}
