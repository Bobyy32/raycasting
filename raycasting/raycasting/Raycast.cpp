#include "Raycast.h"

//void Player::DrawRays(sf::RenderTarget& target)
//{
//	/*mapX = (int)x;
//	mapY = (int)y;*/
//
//	rayAngle = wrap(shape.getRotation() - 60 / 2);
//
//	//credit: https://www.youtube.com/watch?v=gYRrGTC7GtA&t=424s (code inspired from this video since im not good at math!)
//	//credit::: https://lodev.org/cgtutor/raycasting.html explanation behind raycasting
//
//	//casting only one ray but change i < WINDOW_WIDTH (1280) later to cover the whole screen
//
//	for (int i = 0; i < WINDOW_WIDTH; i++)
//	{
//		DepthOfField = 0;
//		float aTan = 1 / tan(rayAngle);
//
//		if (rayAngle > PI)    //looking down
//		{
//			rayY = (((int)y / 64) * 64) - 0.0001;
//			rayX = (y - rayY) * aTan + x;
//			yOffset = -64;
//			xOffset = yOffset * aTan;
//		}
//		else if (rayAngle < PI)    //looking up
//		{
//			rayY = (((int)y / 64) * 64) + 64;
//			rayX = (y - rayY) * aTan + x;
//			yOffset = 64;
//			xOffset = yOffset * aTan;
//		}
//
//		if (rayAngle == 0 || rayAngle == PI) //looking straight left or right
//		{
//			rayX = x;
//			rayY = y;
//			DepthOfField = 24;
//		}
//
//		while (DepthOfField < 24)
//		{
//			mapX = (int)(rayX) / 64;
//			mapY = (int)(rayY) / 64;
//			if (mapPos < mapX * mapY && worldMap[mapY][mapX] > 0) //found a wall
//			{
//				DepthOfField = 24;
//			}
//			else //next line
//			{
//				rayX += xOffset;
//				rayY += yOffset;
//				DepthOfField += 1;
//			}
//		}
//		sf::VertexArray line(sf::Lines, 2);
//		line[0].position = sf::Vector2f(x, y);
//		line[0].color = sf::Color::White;
//		line[1].position = sf::Vector2f(rayX, rayY);
//		line[1].color = sf::Color::White;
//
//		target.draw(line);
//	}



//sf::Vector2f Raycast::raycast(Player player)
//{
//	//credit: https://www.youtube.com/watch?v=gYRrGTC7GtA&t=424s (code inspired from this video since im not good at math!)
//	//credit::: https://lodev.org/cgtutor/raycasting.html explanation behind raycasting
//
//
//	/*float rayAngle = (player.getAngle() * (PI / 180.f) - FOV / 2);*/
//
//	float rayAngleDegrees = wrap(player.getAngle() - FOV / 2);
//	float rayAngle = rayAngleDegrees * (PI / 180.f);
//
//
//	// Loop through all the rays (currently only one ray is being cast)
//	for (int i = 0; i < 1; i++)
//	{
//
//		sf::Vector2f horizonatalIntersect;
//		sf::Vector2f verticalIntersect;
//
//
//		// Calculate the first horizontal intersection
//		if (player.getAngle() < 180)
//		{
//			horizonatalIntersect.y = (((int)player.getY() / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
//			horizonatalIntersect.x = (player.getY() - horizonatalIntersect.y) / tan(rayAngle) + player.getX();
//		}
//		else
//		{
//			horizonatalIntersect.y = (((int)player.getY() / TILE_SIZE) * TILE_SIZE) - 0.0001;
//			horizonatalIntersect.x = (player.getY() - horizonatalIntersect.y) / tan(rayAngle) + player.getX();
//		}
//
//		// Check for horizontal intersections until a wall is hit
//		while (worldMap[(int)horizonatalIntersect.y / TILE_SIZE][(int)horizonatalIntersect.x / TILE_SIZE] == 0)
//		{
//			if (player.getAngle() < 180)
//			{
//				horizonatalIntersect.y += TILE_SIZE;
//				horizonatalIntersect.x = (player.getY() - horizonatalIntersect.y) / tan(rayAngle) + player.getX();
//			}
//			else
//			{
//				horizonatalIntersect.y -= TILE_SIZE;
//				horizonatalIntersect.x = (player.getY() - horizonatalIntersect.y) / tan(rayAngle) + player.getX();
//			}
//		}
//
//		// Calculate the first vertical intersection
//		if (player.getAngle() > 90 && player.getAngle() < 270)
//		{
//			verticalIntersect.x = (((int)player.getX() / TILE_SIZE) * TILE_SIZE) - 0.0001;
//			verticalIntersect.y = (player.getX() - verticalIntersect.x) * tan(rayAngle) + player.getY();
//		}
//		else
//		{
//			verticalIntersect.x = (((int)player.getX() / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
//			verticalIntersect.y = (player.getX() - verticalIntersect.x) * tan(rayAngle) + player.getY();
//		}
//
//		// Check for vertical intersections until a wall is hit
//		while (worldMap[(int)verticalIntersect.y / TILE_SIZE][(int)verticalIntersect.x / TILE_SIZE] == 0)
//		{
//			if (player.getAngle() > 90 && player.getAngle() < 270)
//			{
//				verticalIntersect.x -= TILE_SIZE;
//				verticalIntersect.y = (player.getX() - verticalIntersect.x) * tan(rayAngle) + player.getY();
//			}
//			else
//			{
//				verticalIntersect.x += TILE_SIZE;
//				verticalIntersect.y = (player.getX() - verticalIntersect.x) * tan(rayAngle) + player.getY();
//			}
//		}
//
//		// Calculate the distances to the horizontal and vertical intersections
//		float distanceH = sqrt(pow(player.getX() - horizonatalIntersect.x, 2) + pow(player.getY() - horizonatalIntersect.y, 2));
//		float distanceV = sqrt(pow(player.getX() - verticalIntersect.x, 2) + pow(player.getY() - verticalIntersect.y, 2));
//
//		// Return the closest intersection point (either horizontal or vertical)
//		if (distanceH < distanceV)
//		{
//			return horizonatalIntersect;
//		}
//		else
//		{
//			return verticalIntersect;
//		}
//	}
//}


//sf::Vector2f Raycast::raycast(Player player)
//{
// 	//credit: https://www.youtube.com/watch?v=gYRrGTC7GtA&t=424s (code inspired from this video since im not good at math!)
//    //credit::: https://lodev.org/cgtutor/raycasting.html explanation behind raycasting
//
//    //No actually code used from their video, just the idea of how to do it
//
//
//    for (int i = 0; i < 1; i++)
//    {
//
//        float stepSize = 1.0f;
//        float maxDistance = 1000.0f;
//        sf::Vector2f currentPosition = sf::Vector2f(player.getX(), player.getY());
//
//        for (float currentDistance = stepSize; currentDistance < maxDistance; currentDistance += stepSize)
//        {
//            sf::Vector2f intersection(
//                currentPosition.x + currentDistance * -cos(player.getAngle()),
//                currentPosition.y + currentDistance * -sin(player.getAngle())
//            );
//
//            int mapX = static_cast<int>(intersection.x / TILE_SIZE);
//            int mapY = static_cast<int>(intersection.y / TILE_SIZE);
//
//            if (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY < MAP_HEIGHT)
//            {
//                if (worldMap[mapY][mapX] != 0)
//                {
//                    return intersection;
//                }
//            }
//            else
//            {
//                break; // Out of the map bounds
//            }
//        }
//	}
//
//    return sf::Vector2f(-1, -1); // No intersection found
//}
//
//
//void Raycast::drawRay(sf::RenderWindow& window, const sf::Vector2f& playerPos, const sf::Vector2f& intersection)
//{
//	sf::VertexArray line(sf::Lines, 2);
//
//	line[0].position = playerPos;
//	line[0].color = sf::Color::White;
//	line[1].position = intersection;
//	line[1].color = sf::Color::White;
//
//	window.draw(line);
//}


std::vector<sf::Vector2f> Raycast::raycast(Player player, int numRays, float fov)
{
    std::vector<sf::Vector2f> intersections;
    float angleStep = fov / (numRays - 1);
    float startAngle = player.getAngle() - fov / 2.0f;

    for (int i = 0; i < numRays; i++)
    {
        float currentAngle = startAngle + i * angleStep;
        float stepSize = 1.0f;
        float maxDistance = 1000.0f;
        sf::Vector2f currentPosition = sf::Vector2f(player.getX(), player.getY());

        for (float currentDistance = stepSize; currentDistance < maxDistance; currentDistance += stepSize)
        {
            sf::Vector2f intersection(
                currentPosition.x + currentDistance * -cos(currentAngle),
                currentPosition.y + currentDistance * -sin(currentAngle)
            );

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