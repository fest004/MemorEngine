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
#include "src/A1/circle.hpp"
#include "src/A1/rectangle.hpp"
#include "src/utils/fileread.h"

#include "src/memorlogger/log.hpp"
#include "src/memorlogger/logger.hpp"
int main() {

  Log logger;
  logger.Init();

  // Rectangle* rect = new Rectangle("Felix", 200, 300, 1.0f, 2.0f, sf::Color(0,
  // 100, 100), sf::Vector2f(100.f, 100.0f)); rectangles.push_back(rect);

  sf::RenderWindow window(sf::VideoMode(800, 600), "Memor");
  window.setFramerateLimit(60);

  // Create a font for text rendering
  sf::Font font;
  if (!font.loadFromFile("fonts/arcadeclassic.ttf")) {
    // Error handling if the font file is not found
    MemorCritical("Failed to open the font! ");
    return -1;
  }

  // Create a text object
  sf::Text text;
  text.setFont(font);
  text.setString("Sample Text");
  text.setCharacterSize(12);
  text.setFillColor(sf::Color::Cyan);
  text.setPosition(10, window.getSize().y - text.getGlobalBounds().height - 10);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        logger.Shutdown();
        window.close();
      }
    }

    window.clear();
    window.draw(text);
    window.display();
  }
  return 0;
}
