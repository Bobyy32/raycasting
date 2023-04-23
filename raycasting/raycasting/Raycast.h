#pragma once
#include "Header.h"
#include "Player.h"

const std::vector<std::string> TEXTURE_FILES = {
	"texture/greystone.png",
	"texture/mossy.png",
	"texture/redbrick.png",
	"texture/bluestone.png",
	"texture/wood.png",
	"texture/colorstone.png",
};

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

	std::vector<sf::Vector2f> raycast(Player player);
	void drawRays(sf::RenderWindow& window, const sf::Vector2f& playerPos, const std::vector<sf::Vector2f>& intersections);
	void draw3D(sf::RenderWindow& window, const Player& player, const std::vector<sf::Vector2f>& intersections);

};

