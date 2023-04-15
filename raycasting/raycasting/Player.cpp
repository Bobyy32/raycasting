#include "Player.h"

float wrap(float angle) {
    while (angle >= 360.f) angle -= 360.f;
    while (angle < 0.f) angle += 360.f;
    return angle;
}

Player::Player()
{
    // Initialize player object to a circle shape with radius 7.5 (approx. same size as 15x15 rectangle) and color green
    this->shape.setRadius(7.5f);
    this->shape.setFillColor(sf::Color::Green);

    // Set origin to the center of the shape and set position to 400x300 on the window
    this->shape.setOrigin(sf::Vector2f(7.5f, 7.5f));
    this->shape.setPosition(sf::Vector2f(x, y));
}

//void Player::update(float d_Time)
//{
//    float rotation = this->shape.getRotation();
//
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
//        float rotationSpeed = (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ? -250.f : 250.f) * d_Time;
//        this->shape.rotate(rotationSpeed);
//
//        rotation = wrap(rotation);
//        angle = rotation * DEG_TO_RAD;
//    }
//
//    // Update direction line based on the shape's rotation
//    dx = -cos(angle) * 5;
//    dy = -sin(angle) * 5;
//
//    //object rotation
//    sf::Vector2f direction = sf::Vector2f(std::cos(rotation * DEG_TO_RAD), std::sin(rotation * DEG_TO_RAD));
//    float speed = 250.f;
//
//
//    //object move forward and backward
//    float newX = x, newY = y;
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
//    {
//        newX += dx;
//        newY += dy;
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
//    {
//        newX -= dx;
//        newY -= dy;
//    }
//
//    // Calculate the corner positions for collision checks
//    float radius = this->shape.getRadius();
//    float margin = 0.5 * TILE_SIZE;
//    //Thanks to https://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection
//    //And to my friend brayden at Virginia Tech lol
//    float cornerX[4] = { newX - radius + margin, newX + radius - margin, newX + radius - margin, newX - radius + margin };
//    float cornerY[4] = { newY - radius + margin, newY - radius + margin, newY + radius - margin, newY + radius - margin };
//
//    bool collision = false;
//
//    // Check for collision with walls
//    for (int i = 0; i < 4; i++) {
//        int mapX = static_cast<int>(cornerX[i] / TILE_SIZE);
//        int mapY = static_cast<int>(cornerY[i] / TILE_SIZE);
//
//        // Check if the corner is within the map bounds
//        if (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY < MAP_HEIGHT)
//        {
//            // If the tile at the corner position is a wall, set collision flag to true
//            if (worldMap[mapY][mapX] != 0)
//            {
//                collision = true;
//                break;
//            }
//        }
//    }
//
//    if (!collision)
//    {
//        x = newX;
//        y = newY;
//        this->shape.setPosition(sf::Vector2f(x, y));
//    }
//
//    // Update position
//    x = this->shape.getPosition().x;
//    y = this->shape.getPosition().y;
//}

void Player::update(float d_Time)
{
    float rotation = this->shape.getRotation() * DEG_TO_RAD; // Convert the initial rotation to radians

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        float rotationSpeed = (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ? -5.f : 5.f) * d_Time;
        this->shape.rotate(rotationSpeed * RAD_TO_DEG); // Convert rotation speed to degrees for SFML

        rotation = wrap(rotation);
        angle = rotation;
    }

    // Update direction line based on the shape's rotation
    dx = -cos(angle) * 5;
    dy = -sin(angle) * 5;

    //object rotation
    sf::Vector2f direction = sf::Vector2f(std::cos(rotation), std::sin(rotation));
    float speed = 250.f;

    //collision detection

    //object move forward and backward
    float newX = x, newY = y;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        newX += dx;
        newY += dy;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        newX -= dx;
        newY -= dy;
    }

    // Calculate the corner positions for collision checks
    float radius = this->shape.getRadius();
    float margin = 0.5 * TILE_SIZE;
    //Thanks to https://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection
   //And to my friend brayden at Virginia Tech lol
    float cornerX[4] = { newX - radius + margin, newX + radius - margin, newX + radius - margin, newX - radius + margin };
    float cornerY[4] = { newY - radius + margin, newY - radius + margin, newY + radius - margin, newY + radius - margin };

    bool collision = false;

    // Check for collision with walls
    for (int i = 0; i < 4; i++) {
        int mapX = static_cast<int>(cornerX[i] / TILE_SIZE);
        int mapY = static_cast<int>(cornerY[i] / TILE_SIZE);

        // Check if the corner is within the map bounds
        if (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY < MAP_HEIGHT)
        {
            // If the tile at the corner position is a wall, set collision flag to true
            if (worldMap[mapY][mapX] != 0)
            {
                collision = true;
                break;
            }
        }
    }

    if (!collision)
    {
        x = newX;
        y = newY;
        this->shape.setPosition(sf::Vector2f(x, y));
    }

    // Update position
    x = this->shape.getPosition().x;
    y = this->shape.getPosition().y;
}


void Player::draw(sf::RenderTarget& target)
{
	target.draw(this->shape);


	// Draw direction line for the player
	sf::VertexArray directionLine(sf::Lines, 2);
	directionLine[0].position = sf::Vector2f(x, y);
	directionLine[1].position = sf::Vector2f(x + dx * 25, y + dy * 25);	//adjust the length of the line
	directionLine[0].color = sf::Color::Blue;
	directionLine[1].color = sf::Color::Blue;
	
	target.draw(directionLine);

}

