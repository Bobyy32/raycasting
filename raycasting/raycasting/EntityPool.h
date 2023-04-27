#pragma once
#include "Header.h"
#include "Player.h"
#include "Entity.h"
#include "Entity_1.h"
#include "Entity_2.h"

class EntityPool
{
	private:
	std::vector<Entity*> entities;
public:
	EntityPool();
	~EntityPool();

	std::vector<Entity*> getEntities()const { return this->entities; }

	void addEntity(const int& round);

	sf::Vector2f randSpawn(int map[][MAP_WIDTH]);

	void updateEntities(const float& d_Time, const Player& player, int& round, int& score);

	int isEmpty()const { return this->entities.size() == 0; }

	void removeEntity(const int& index);


};

