#pragma once
#include "Header.h"


class Entity
{
protected:
	sf::Vector2f position;	//sprite position
	float speed;
	sf::Sprite sprite;

public:
	Entity();
	Entity(sf::Vector2f& pos);
	virtual ~Entity();

	virtual void update(const float& d_Time) = 0;

	sf::Vector2f getPos()const { return this->position; }
	void setPos(sf::Vector2f& pos) { this->position = pos; }
};