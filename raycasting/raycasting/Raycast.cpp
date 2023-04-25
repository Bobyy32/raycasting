#include "Raycast.h"

#include <vector>
#include <utility> // for std::pair

std::vector<std::pair<sf::Vector2f, float>> Raycast::raycast(const Player& player, const EntityPool& entityPool)
{
    //credit: https://www.youtube.com/watch?v=gYRrGTC7GtA&t=424s (code inspired from this video since im not good at math!)
    //credit::: https://lodev.org/cgtutor/raycasting.html explanation behind raycasting

    int numRays = WINDOW_WIDTH;
    std::vector<std::pair<sf::Vector2f, float>> intersections;

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
                    intersections.push_back(std::make_pair(intersection, currentDistance));
                    break;
                }
            }
            else
            {
                break; // Out of map bounds
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

void Raycast::draw3D(sf::RenderWindow& window, const Player& player, const EntityPool& entityPool, const std::vector<std::pair<sf::Vector2f, float>>& intersections)
{
    sf::RectangleShape line;
    float viewAngle = player.getAngle();
    float fov = (FOV * PI) / 180.0f; // Convert FOV to radians


    sf::Color brightColor = sf::Color::White;
    sf::Color darkColor = sf::Color(0, 0, 0); // Dark red

    for (int i = 0; i < intersections.size(); i++)
    {
        float rayAngle = viewAngle - (fov / 2) + (i * fov / (intersections.size() - 1));
        float distance = std::sqrt(std::pow(player.getX() - intersections[i].first.x, 2) + std::pow(player.getY() - intersections[i].first.y, 2));

        // Fish eye effect fix (IMPORTANT)
        float correctedDistance = distance * cos(viewAngle - rayAngle);
        float lineHeight = (WINDOW_HEIGHT / correctedDistance) * 100;

        // Shading based on distance
        float shadingFactor = correctedDistance / 1000.0f; 
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

void Raycast::drawSprites(sf::RenderWindow& window, const Player& player, const EntityPool& entityPool, const std::vector<std::pair<sf::Vector2f, float>>& intersections)
{
    std::vector<Entity*> entities = entityPool.getEntities();
    std::vector<std::pair<Entity*, float>> entitiesWithDistance;

    // Calculate the distance between the player and each entity
    for (Entity* entity : entities)
    {
        sf::Vector2f entityPos = entity->getPos();
        float dx = player.getX() - entityPos.x;
        float dy = player.getY() - entityPos.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        entitiesWithDistance.push_back(std::make_pair(entity, distance));
    }

    // Sort the entities by distance (descending order)
    std::sort(entitiesWithDistance.begin(), entitiesWithDistance.end(), [](const std::pair<Entity*, float>& a, const std::pair<Entity*, float>& b)
        {
            return a.second > b.second;
        });

    // Draw the entities
    for (const auto& entityWithDistance : entitiesWithDistance)
    {
        Entity* entity = entityWithDistance.first;
        float distance = entityWithDistance.second;

        sf::Sprite sprite = entity->getSprite();
        sf::Vector2f entityPos = entity->getPos();

        // Calculate the relative position of the entity to the player
        float dx = entityPos.x - player.getX();
        float dy = entityPos.y - player.getY();

        // Calculate the angle between the player's view and the entity
        float viewAngle = player.getAngle();
        float angleToEntity = atan2(dy, dx) - viewAngle;

        // Project the sprite's position onto the player's view plane (2d camera matrix)
        float spriteScreenX = (WINDOW_WIDTH / 2) + (WINDOW_WIDTH / 2) * tan(angleToEntity) / tan(FOV * PI / 360.0f);

        // Calculate the sprite's height and scale
        float spriteHeight = (WINDOW_HEIGHT / distance) * 100;
        float spriteScale = spriteHeight / sprite.getTextureRect().height;

        // Set the sprite's position, scale, and orientation
        sprite.setScale(spriteScale, spriteScale);
        sprite.setPosition(spriteScreenX - sprite.getGlobalBounds().width / 2, (WINDOW_HEIGHT / 2) - (spriteHeight / 2));

        // Draw the sprite
        window.draw(sprite);
    }
}






