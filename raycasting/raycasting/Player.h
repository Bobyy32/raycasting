#pragma once
#include "Header.h"

class Player
{
private:
	sf::RectangleShape shape;

	Position pos;

public:
	Player();
	
	void update(float d_Time); //delta time
	void draw(sf::RenderTarget& target);

	Position getPos() { return this->pos; }
};

