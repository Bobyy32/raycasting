#include "Raycast.h"

Raycast::Raycast() 
{
    loadTextures(TEXTURE_FILES);
}

void Raycast::loadTextures(const std::vector<std::string>& textureFiles) 
{
    for (const std::string& textureFile : textureFiles) {
        sf::Texture texture;
        if (!texture.loadFromFile(textureFile)) {
            std::cout << "Failed to load texture: " << textureFile << std::endl;
        }
        textures.push_back(texture);
    }
}


std::vector<std::pair<sf::Vector2f, bool>> Raycast::raycast(Player player)
{
 	//credit: https://www.youtube.com/watch?v=gYRrGTC7GtA&t=424s (code inspired from this video since im not good at math!)
    //credit::: https://lodev.org/cgtutor/raycasting.html explanation behind raycasting

    int numRays = WINDOW_WIDTH;
    std::vector<std::pair<sf::Vector2f, bool>> intersections;

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
                    bool isHorizontalWall = fabs(floor(intersection.y / TILE_SIZE) * TILE_SIZE - intersection.y) < 1e-4;
                    intersections.push_back(std::make_pair(intersection, isHorizontalWall));
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

void Raycast::draw3D(sf::RenderWindow& window, const Player& player, const std::vector<std::pair<sf::Vector2f, bool>>& intersections)
{
    sf::RectangleShape line;
    float viewAngle = player.getAngle();
    float fov = (FOV * PI) / 180.0f; // Convert FOV to radians

    for (int i = 0; i < intersections.size(); i++)
    {
        float rayAngle = viewAngle - (fov / 2) + (i * fov / (intersections.size() - 1));
        float distance = std::sqrt(std::pow(player.getX() - intersections[i].first.x, 2) + std::pow(player.getY() - intersections[i].first.y, 2));

        // Fish eye effect fix (IMPORTANT)
        float correctedDistance = distance * cos(viewAngle - rayAngle);
        float lineHeight = (WINDOW_HEIGHT / correctedDistance) * 100;

        int mapX = static_cast<int>(intersections[i].first.x / TILE_SIZE);
        int mapY = static_cast<int>(intersections[i].first.y / TILE_SIZE);

        // Calculate texture coordinates
        float textureX;
        if (intersections[i].second) { // Horizontal wall
            textureX = intersections[i].first.x - floor(intersections[i].first.x / TILE_SIZE) * TILE_SIZE;
        }
        else { // Vertical wall
            textureX = intersections[i].first.y - floor(intersections[i].first.y / TILE_SIZE) * TILE_SIZE;
        }
        textureX /= TILE_SIZE; // Normalize texture coordinates

        // Choose the texture based on the wall type in the world map
        int textureIndex = worldMap[mapY][mapX];
        const sf::Texture& texture = textures[textureIndex];

        line.setSize(sf::Vector2f(1, lineHeight));
        line.setPosition(sf::Vector2f(i, (WINDOW_HEIGHT / 2) - (lineHeight / 2)));
        line.setTexture(&texture);
        line.setTextureRect(sf::IntRect(static_cast<int>(textureX * texture.getSize().x), 0, 1, texture.getSize().y));

        // Apply shading based on distance
        float shadingFactor = correctedDistance / 1000.0f; // Assuming maxDistance = 1000.0f in raycast function
        sf::Color shadingColor = sf::Color(255 * (1 - shadingFactor), 255 * (1 - shadingFactor), 255 * (1 - shadingFactor), 255);

        line.setFillColor(shadingColor);
        window.draw(line);
    }
}



