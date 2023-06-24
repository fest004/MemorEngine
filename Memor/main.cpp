// STD Headers
#include <iostream>

// SFML Headers
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

// Memor headers
#include "src/utils/fileread.h"
#include "src/A1/rectangle.hpp"
#include "src/A1/circle.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Floating Ball");
    window.setFramerateLimit(60);

    // Create a red ball shape
    // sf::CircleShape ball(50);
    // ball.setFillColor(sf::Color::Red);
    // ball.setPosition(400, 300);
    // float circleSpeedX = 0.2f;
    // float circleSpeedY = 0.1f;

    //Create Rectangle shape
    // sf:sf::RectangleShape rectangle(sf::Vector2f(100.f, 100.0f));
    // rectangle.setFillColor(sf::Color(100, 20, 244));
    // rectangle.setPosition(100, 100);
    // float rectSpeedX = 0.1f;
    // float rectSpeedY = 0.2f;

    Rectangle* rect = new Rectangle("Felix", 100, 200, 2.0f, 2.0f, sf::Color(0, 100, 100), sf::Vector2f(100.f, 100.0f));
    Circle* circle = new Circle("Arl", 100, 200, 3.0f, 3.0f, sf::Color(100, 100, 0), 50);

    // Create a font for text rendering
    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        // Error handling if the font file is not found
        return -1;
    }

    // Create a text object
    sf::Text text;
    text.setFont(font);
    text.setString("Sample Text");
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, window.getSize().y - text.getGlobalBounds().height - 10);

    FileReader* fileReader = new FileReader();
    std::string config = fileReader->ReadFile("temp/A1/config.txt");
    std::cout << config << std::endl;
    std::cout << fileReader->getLength() << std::endl;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Move the stuff
        rect->Move();
        circle->Move();

        // Check if the ball hits the window bounds

        rect->CheckCollision(window.getSize().x, window.getSize().y);
        circle->CheckCollision(window.getSize().x, window.getSize().y);
        window.clear();
        rect->Draw(window, text);
        circle->Draw(window, text);
        window.draw(text);
        window.display();
    }
    return 0;
}

