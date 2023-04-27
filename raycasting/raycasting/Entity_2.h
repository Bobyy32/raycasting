#pragma once
#include "Header.h"
#include "Entity.h"


class Entity_2 : public Entity
{
	public:
	Entity_2();
	Entity_2(sf::Vector2f& pos);
	~Entity_2();
	void update(const float& d_Time, const Player& player) override;
};

