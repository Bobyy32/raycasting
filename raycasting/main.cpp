//sean duffy
#include <SFML/Graphics.hpp>

int main()
{
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game Menu");

    // Create the "Play" button
    sf::RectangleShape playButton(sf::Vector2f(200, 50));
    playButton.setPosition(sf::Vector2f(300, 200));
    playButton.setFillColor(sf::Color::Green);

    // Create the "Instructions" button
    sf::RectangleShape instructionsButton(sf::Vector2f(200, 50));
    instructionsButton.setPosition(sf::Vector2f(300, 300));
    instructionsButton.setFillColor(sf::Color::Blue);

    // Create the "Exit" button
    sf::RectangleShape exitButton(sf::Vector2f(200, 50));
    exitButton.setPosition(sf::Vector2f(300, 400));
    exitButton.setFillColor(sf::Color::Red);

    // Run the game loop
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // Check if the "Play" button was clicked
                    if (playButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        // TODO: Start the game
                    }

                    // Check if the "Instructions" button was clicked
                    if (instructionsButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        // TODO: Show the instructions
                    }

                    // Check if the "Exit" button was clicked
                    if (exitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        window.close();
                    }
                }
                break;

            default:
                break;
            }
        }

        // Clear the window
        window.clear();

        // Draw the buttons
        window.draw(playButton);
        window.draw(instructionsButton);
        window.draw(exitButton);

        // Display the window
        window.display();
    }

    return 0;
}