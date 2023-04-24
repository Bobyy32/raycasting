#pragma once
#include "Header.h"
#include "Player.h"
#include "EntityPool.h"

class Raycast
{

private:


public:

	float wrap(float angle) //useless code
	{
		while (angle >= 360.f) angle -= 360.f;
		while (angle < 0.f) angle += 360.f;
		return angle;
	}

	std::vector<sf::Vector2f> raycast(const Player& player, const EntityPool& entityPool);
	void drawRays(sf::RenderWindow& window, const sf::Vector2f& playerPos, const std::vector<sf::Vector2f>& intersections);
	void draw3D(sf::RenderWindow& window, const Player& player, const EntityPool& entityPool, const std::vector<sf::Vector2f>& intersections);

};

