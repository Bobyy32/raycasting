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
	std::vector<sf::Texture> textures;

public:
	Raycast();

	void loadTextures(const std::vector<std::string>& textureFiles);


	float wrap(float angle) //useless code
	{
		while (angle >= 360.f) angle -= 360.f;
		while (angle < 0.f) angle += 360.f;
		return angle;
	}

	//std::vector<sf::Vector2f> raycast(Player player);
	std::vector<std::pair<sf::Vector2f, bool>> raycast(Player player);	//reason for change is to maybe add a bool to the vector to see if the ray hit a wall or not

	void drawRays(sf::RenderWindow& window, const sf::Vector2f& playerPos, const std::vector<sf::Vector2f>& intersections);

	void draw3D(sf::RenderWindow& window, const Player& player, const std::vector<std::pair<sf::Vector2f, bool>>& intersections);

};

