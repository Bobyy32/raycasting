#pragma once
#include "Header.h"

class Player
{
private:
	sf::CircleShape shape;

	//position
	//this is to keep track of the position of the player
	int spwnX = 5;
	int spwnY = 5;

	float x = static_cast<float>(spwnX * TILE_SIZE);
	float y = static_cast<float>(spwnY * TILE_SIZE);

	/*float x = 100;
	float y = 100;*/

	//angle
	float angle = 0;

	//change in x and y
	float dx = 0;
	float dy = 0;

public:
	Player();
	
	void update(float d_Time); //delta time
	void draw(sf::RenderTarget& target);

	/*bool checkCollision(int x, int y, const int worldMap[][MAP_WIDTH]);*/

	//getters
	float getX()const { return this->x; }
	float getY()const { return this->y; }
	float getAngle()const { return this->angle; }
	float getDX()const { return this->dx; }
	float getDY()const { return this->dy; }
};

