#pragma once
#include "Header.h"
#include "Entity.h"


class Entity_1: public Entity
{
public:
	Entity_1();
	Entity_1(sf::Vector2f& pos);
	~Entity_1();

	void update(const float& d_Time, const Player& player) override;
};

