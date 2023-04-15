#pragma once
#include "Header.h"

class Player
{
private:
	sf::CircleShape shape;

	//position
	float x = 400;
	float y = 400;

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

