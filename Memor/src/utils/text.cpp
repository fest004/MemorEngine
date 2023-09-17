#include "text.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <iostream>


namespace utils
{

void CenterText(sf::Text& text, sf::Window& window);

void CenterText(sf::Text& text, sf::Window& window)
{
  sf::FloatRect textRect = text.getLocalBounds();

  text.setOrigin
  (
    textRect.left + textRect.width/2.0f,
    textRect.top + textRect.height/2.0f
  );

  text.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y/2.0f));

}


//Takes in text, window and scale. Scales text relative to window in based of off float scale. Argument 20 = 20% of screen size
void ResizeText(sf::Text& text, sf::Window& window, float scale)
{
  int newSize = static_cast<int>((window.getSize().y / 100.0f) * scale);

  text.setCharacterSize(newSize);
}


}


