#include "Raycast.h"

std::vector<sf::Vector2f> Raycast::raycast(Player player)
{
 	//credit: https://www.youtube.com/watch?v=gYRrGTC7GtA&t=424s (code inspired from this video since im not good at math!)
    //credit::: https://lodev.org/cgtutor/raycasting.html explanation behind raycasting

    int numRays = WINDOW_WIDTH;
    std::vector<sf::Vector2f> intersections;

    // Convert FOV to radians and wrap the angle in radians
    float radiansFOV = (FOV * PI) / 180.0f;
    float rayAngle = player.getAngle() - radiansFOV / 2;

    for (int i = 0; i < numRays; i++)
    {

        float stepSize = 1.0f;
        float maxDistance = 1000.0f;
        sf::Vector2f currentPosition = sf::Vector2f(player.getX(), player.getY());

        for (float currentDistance = stepSize; currentDistance < maxDistance; currentDistance += stepSize)
        {
            sf::Vector2f intersection(currentPosition.x + currentDistance * -cos(rayAngle), currentPosition.y + currentDistance * -sin(rayAngle));

            int mapX = static_cast<int>(intersection.x / TILE_SIZE);
            int mapY = static_cast<int>(intersection.y / TILE_SIZE);

            if (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY < MAP_HEIGHT)
            {
                if (worldMap[mapY][mapX] != 0)
                {
                    intersections.push_back(intersection);
                    break;
                }
            }
            else
            {
                break; // Out of the map bounds
            }
        }

        // Increment ray angle by the angular step in radians
        float angularStep = radiansFOV / (numRays - 1);
        rayAngle += angularStep;
    }

    return intersections;
}

void Raycast::drawRays(sf::RenderWindow& window, const sf::Vector2f& playerPos, const std::vector<sf::Vector2f>& intersections)
{
    for (const sf::Vector2f& intersection : intersections)
    {
		sf::VertexArray line(sf::Lines, 2);
		line[0].position = playerPos;
		line[0].color = sf::Color::White;
		line[1].position = intersection;
		line[1].color = sf::Color::White;
		window.draw(line);
	}
}

void Raycast::draw3D(sf::RenderWindow& window, const Player& player, const std::vector<sf::Vector2f>& intersections)
{
    sf::RectangleShape line;
    float viewAngle = player.getAngle();
    float fov = (FOV * PI) / 180.0f; // Convert FOV to radians
    /*int screenWidth = 800;
    int screenHeight = 600;*/

    sf::Color brightColor = sf::Color::White;
    sf::Color darkColor = sf::Color(0,0,0); // Dark red

    for (int i = 0; i < intersections.size(); i++)
    {
        float rayAngle = viewAngle - (fov / 2) + (i * fov / (intersections.size() - 1));
        float distance = std::sqrt(std::pow(player.getX() - intersections[i].x, 2) + std::pow(player.getY() - intersections[i].y, 2));

        // Fish eye effect fix (IMPORTANT)
        float correctedDistance = distance * cos(viewAngle - rayAngle);
        float lineHeight = (WINDOW_HEIGHT / correctedDistance) * 100;

        // Shading based on distance
        float shadingFactor = correctedDistance / 1000.0f; // Assuming maxDistance = 1000.0f in raycast function
        sf::Color shadedColor = sf::Color(
            brightColor.r + shadingFactor * (darkColor.r - brightColor.r),
            brightColor.g + shadingFactor * (darkColor.g - brightColor.g),
            brightColor.b + shadingFactor * (darkColor.b - brightColor.b)
        );

        line.setSize(sf::Vector2f(1, lineHeight));
        line.setPosition(sf::Vector2f(i, (WINDOW_HEIGHT / 2) - (lineHeight / 2)));
        line.setFillColor(shadedColor);
        window.draw(line);
    }
}

