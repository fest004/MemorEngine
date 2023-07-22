// STD Headers
#include <SFML/Graphics/Color.hpp>
#include <iostream>

// SFML Headers
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <fstream>
#include <sstream>
#include <string>

// Memor headers
#include "src/memor.hpp"
#include "src/utils/fileread.h"

#include "src/memorlogger/log.hpp"
#include "src/memorlogger/logger.hpp"
int main() {

  Log logger;
  logger.Init();

  MemorGame memor("temp/A2/config.txt");
  memor.run();

  return 0;
}
