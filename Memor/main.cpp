#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Floating Ball");

    // Create a red ball shape
    sf::CircleShape ball(50);
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(400, 300);

    // Define the floating speed of the ball
    float speedX = 0.2f;
    float speedY = 0.1f;

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
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, window.getSize().y - text.getGlobalBounds().height - 10);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Move the ball
        ball.move(speedX, speedY);

        // Check if the ball hits the window bounds
        if (ball.getPosition().x + ball.getRadius() > window.getSize().x || ball.getPosition().x - ball.getRadius() < 0)
            speedX = -speedX;
        if (ball.getPosition().y + ball.getRadius() > window.getSize().y || ball.getPosition().y - ball.getRadius() < 0)
            speedY = -speedY;

        window.clear();
        window.draw(ball);
        window.draw(text);
        window.display();
    }

    return 0;
}

