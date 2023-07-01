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
#include "src/utils/fileread.h"
#include "src/memor.hpp"

#include "src/memorlogger/log.hpp"
#include "src/memorlogger/logger.hpp"
int main() {

  Log logger;
  logger.Init();

  const std::string fp = "test";

  Memor memor(fp);
  memor.Run();



  return 0;
}
