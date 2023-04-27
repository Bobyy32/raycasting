/************************************************************************
* Programmer: Elang Edward Sisson                                       *
* Class: CptS 122;				                                        *
* Programming Assignment: 9									            *
* Date:																	*
*                                                                       *
* Description: Raycast Game 											*
*																		*
*                                                                       *
* Relevant Formulas:													*
*																		*
************************************************************************/
#include "EntityPool.h"

EntityPool::EntityPool()
{

}

EntityPool::~EntityPool()
{

}

void EntityPool::addEntity(const int& round)
{
	int num_entities = round;

	// Seed the random number generator with the current time
	srand(static_cast<unsigned int>(time(0)));

	for (int i = 0; i < num_entities; i++)
	{
		sf::Vector2f spwn = randSpawn(worldMap);

		// Generate a random number between 1 and 2 to determine which entity to spawn
		int entityType = rand() % 2 + 1;
		Entity* entity = nullptr;
		if (entityType == 1)
		{
			entity = new Entity_1(spwn);
		}
		else if (entityType == 2)
		{
			entity = new Entity_2(spwn);
		}

		if (entity != nullptr)
		{
			entities.push_back(entity);
		}
	}
}

sf::Vector2f EntityPool::randSpawn(int map[][MAP_WIDTH])
{	
	int x = 0;
	int y = 0;
	do
	{
		x = rand() % MAP_WIDTH + 1;
		y = rand() % MAP_HEIGHT + 1;
	} while (map[x][y] != 0);

	return sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE);
}

void EntityPool::updateEntities(const float& d_Time,const Player& player, int& round, int& score)
{
	if (entities.size() == 0)
	{
		addEntity(round);
		round++;
	}

	for (int i = 0; i < entities.size(); i++)
	{
		if (entities.at(i)->isDead() == true)
		{
			score += 10;
			delete entities.at(i);
			entities.erase(entities.begin() + i);
		}
		else
		{
			if (entities[i]->getName() == "Entity_1")
			{
				dynamic_cast<Entity_1*>(entities[i])->update(d_Time, player);
			}
			else if (entities[i]->getName() == "Entity_2")
			{
				dynamic_cast<Entity_2*>(entities[i])->update(d_Time, player);
			}
		}
	}
}

void EntityPool::removeEntity(const int& index)
{
	delete entities.at(index);
	entities.erase(entities.begin() + index);
}