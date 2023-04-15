#pragma once
#include "Header.h"
#include "Player.h"


class Raycast
{

private:

public:
	/*sf::Vector2f raycast(Player player);
	void drawRay(sf::RenderWindow& window, const sf::Vector2f& playerPos, const sf::Vector2f& intersection);*/
	float wrap(float angle) {
		while (angle >= 360.f) angle -= 360.f;
		while (angle < 0.f) angle += 360.f;
		return angle;
	}

	std::vector<sf::Vector2f> raycast(Player player, int numRays, float fov);
	void drawRays(sf::RenderWindow& window, const sf::Vector2f& playerPos, const std::vector<sf::Vector2f>& intersections);


};

