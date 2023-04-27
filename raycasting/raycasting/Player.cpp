/************************************************************************
* Programmer: Elang Edward Sisson                                       *
* Class: CptS 122;				                                        *
* Programming Assignment: 9									            *
* Date:																	*
*                                                                       *
* Description: Raycast Game 											*
*																		*
*                                                                       *
* Relevant Formulas:													*
*																		*
************************************************************************/
#include "Player.h"

float wrap(float angle) {
    while (angle >= 360.f) angle -= 360.f;
    while (angle < 0.f) angle += 360.f;
    return angle;
}

Player::Player()
{


    float radius = TILE_SIZE * 0.20f;
    shape.setRadius(radius);

    // Set origin to the center of the shape
    shape.setOrigin(sf::Vector2f(radius, radius));

    shape.setFillColor(sf::Color::Green);
}

void Player::update(float d_Time)
{
    float rotation = this->shape.getRotation() * DEG_TO_RAD; // Convert the rotation to radians

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) || sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
        float rotationSpeed = (sf::Keyboard::isKeyPressed(sf::Keyboard::J) ? -2.f : 2.f) * d_Time;
        this->shape.rotate(rotationSpeed * RAD_TO_DEG); // Convert rotation speed to degrees for SFML

        rotation = wrap(rotation);
        angle = rotation;
    }

    // Update direction line based on the shape's rotation
    dx = -cos(angle) * 5;
    dy = -sin(angle) * 5;

    //object rotation
    sf::Vector2f direction = sf::Vector2f(std::cos(rotation), std::sin(rotation));


    //object move forward and backward
    float newX = x, newY = y;
    float referenceTileSize = (float)TILE_SIZE;
    float referenceSpeed = 0.5f; // reference speed
    float tileSizeRatio = TILE_SIZE / referenceTileSize;
    float speedFactor = referenceSpeed * tileSizeRatio;
    //FAILED attempt at scaling speed to tile size guess ill just keep it here
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        newX += speedFactor * dx;
        newY += speedFactor * dy;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        newX -= speedFactor * dx;
        newY -= speedFactor * dy;
    }

    //object move left and right
    float perpendicularX = -direction.y;
    float perpendicularY = direction.x;

    float lateralSpeedFactor = speedFactor * 5.0f;  //fix for diagonal slow movement

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        newX += lateralSpeedFactor * perpendicularX;
        newY += lateralSpeedFactor * perpendicularY;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        newX -= lateralSpeedFactor * perpendicularX;
        newY -= lateralSpeedFactor * perpendicularY;
    }

    //collision detection (absolute dogshit i gotta fix this omg so annoying help)
    // 
    // 
    // Calculate the corner positions for collision checks
    float radius = this->shape.getRadius();
    float margin = 0.5 * TILE_SIZE;

    //Thanks to https://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection
   //And to my friend brayden at Virginia Tech lol
    float cornerX[4] = { newX - radius + margin, newX + radius - margin, newX + radius - margin, newX - radius + margin };
    float cornerY[4] = { newY - radius + margin, newY - radius + margin, newY + radius - margin, newY + radius - margin };

    bool collision = false;

    // Check for collision with walls in X direction
    bool collisionX = false;
    for (int i = 0; i < 4; i++) {
        int mapX = static_cast<int>(cornerX[i] / TILE_SIZE);
        int mapY = static_cast<int>(cornerY[i] / TILE_SIZE);

        if (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY < MAP_HEIGHT)
        {
            if (worldMap[mapY][mapX] != 0)
            {
                collisionX = true;
                break;
            }
        }
    }

    // Update X position if no collision in X direction
    if (!collisionX)
    {
        x = newX;
    }

    // Check for collision with walls in Y direction
    bool collisionY = false;
    for (int i = 0; i < 4; i++) {
        int mapX = static_cast<int>(cornerX[i] / TILE_SIZE);
        int mapY = static_cast<int>(cornerY[i] / TILE_SIZE);

        if (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY < MAP_HEIGHT)
        {
            if (worldMap[mapY][mapX] != 0)
            {
                collisionY = true;
                break;
            }
        }
    }

    // Update Y position if no collision in Y direction
    if (!collisionY)
    {
        y = newY;
    }

    this->shape.setPosition(sf::Vector2f(x, y));

    // Update position
    x = this->shape.getPosition().x;
    y = this->shape.getPosition().y;
}


void Player::draw(sf::RenderTarget& target)     //this is for drawing the player in a 2d space (testing before i added 3d)
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

