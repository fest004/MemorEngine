// STD Headers
#include <SFML/Graphics/Color.hpp>
#include <iostream>

// SFML Headers
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <string>
#include <fstream>
#include <sstream>

// Memor headers
#include "src/utils/fileread.h"
#include "src/A1/rectangle.hpp"
#include "src/A1/circle.hpp"

int main()
{
/*
Window 800 600
Font fonts/arial.ttf 18 255 255 255
Circle CGreen 100 100 -0.03 0.02 0 255 0 50
Rectangle RRed 200 200 0.1 0.15 255 0 0 50 25
*/
    int windowWidth = 800;
    int windowHeight = 600;
    std::vector<Rectangle*> rectangles;
    std::vector<Circle*> circles;

    std::string fontPath = "fonts/arial.ttf";
    int fontSize = 12;
    sf::Color fontColor(255, 255, 255);

    std::fstream file("temp/A1/config.txt");

    if (file.is_open()) {
        std::cout << "File opened" << std::endl;
        std::string currentLine;
        while (std::getline(file, currentLine)) 
        {
            std::istringstream iss(currentLine);
            std::string value;
            std::vector<std::string> values;

            while (iss >> value) 
            {
                values.push_back(value);
            }

            if(values.empty()) 
            {
                std::cout << "File empty";
                break;
            }

            if (values[0] == "Window") 
            {
                windowWidth = std::stoi(values[1]);
                windowHeight = std::stoi(values[2]);
                continue;
            }

            if (values[0] == "Font")
            {
                //Font fonts/arial.ttf 18 255 255 255
                std::cout << "Made to fonts" << std::endl;
                fontPath = values[1];
                std::cout << fontPath << std::endl;
                fontSize = std::stoi(values[2]);
                fontColor = sf::Color(std::stoi(values[3]), std::stoi(values[4]), std::stoi(values[5]));
            }

            if (values[0] == "Circle")
            {
                //Circle CGreen 100 100 -0.03 0.02 0 255 0 50
                std::string name = values[1];
                int xPos = std::stoi(values[2]);
                int yPos = std::stoi(values[3]);
                float xSpeed = std::stof(values[4]);
                float ySpeed = std::stof(values[5]);
                sf::Color color(std::stoi(values[6]), std::stoi(values[7]), std::stoi(values[8]));
                int r = std::stoi(values[9]);

                Circle* circle = new Circle(name, xPos, yPos, xSpeed, ySpeed, color, r);
                circles.push_back(circle);
            }

            if (values[0] == "Rectangle")
            {
                //Rectangle RRed 200 200 0.1 0.15 255 0 0 50 25
                std::string name = values[1];
                int xPos = std::stoi(values[2]);
                int yPos = std::stoi(values[3]);
                float xSpeed = std::stof(values[4]);
                float ySpeed = std::stof(values[5]);
                sf::Color color(std::stoi(values[6]), std::stoi(values[7]), std::stoi(values[8]));
                sf::Vector2f size(std::stof(values[9]), std::stof(values[10]));

                Rectangle* rect = new Rectangle(name, xPos, yPos, xSpeed, ySpeed, color, sf::Vector2f(100.f, 100.0f));
                rectangles.push_back(rect);
            }
        }
        file.close();
    } else {
        std::cout << "Failed to open file" << std::endl;
    }



    // Rectangle* rect = new Rectangle("Felix", 200, 300, 1.0f, 2.0f, sf::Color(0, 100, 100), sf::Vector2f(100.f, 100.0f));
    // rectangles.push_back(rect);



    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Memor");
    window.setFramerateLimit(60);


    // Create a font for text rendering
    sf::Font font;
    if (!font.loadFromFile(fontPath))
    {
        // Error handling if the font file is not found
        std::cout << "Font not found!" << std::endl;
        return -1;
    }

    // Create a text object
    sf::Text text;
    text.setFont(font);
    text.setString("Sample Text");
    text.setCharacterSize(fontSize);
    text.setFillColor(fontColor);
    text.setPosition(10, window.getSize().y - text.getGlobalBounds().height - 10);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (auto rect : rectangles) {
            rect->Move();
            rect->CheckCollision(window.getSize().x, window.getSize().y);
            rect->Draw(window, text);
        }

        for (auto circle : circles) {
            circle->Move();
            circle->CheckCollision(window.getSize().x, window.getSize().y);
            circle->Draw(window, text);
        }
        window.draw(text);
        window.display();
    }
    return 0;
}

