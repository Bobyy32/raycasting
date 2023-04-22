#pragma once
#include "Header.h"
#include "Entity.h"


class Entity_1: public Entity
{
public:
	Entity_1(sf::Vector2f& pos);
	virtual ~Entity_1();
	void update(const float& d_Time) override;
};

