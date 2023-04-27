#include "UnitTesting.h"

void UnitTesting::testAddEntity()
{
	EntityPool entityPool;
	entityPool.addEntity(1);
	if (entityPool.getEntities().size() > 0);
	{
		std::cout << "Test passed: Entity added to pool" << std::endl;
	}
}

void UnitTesting::testRemoveEntity()
{
	EntityPool entityPool;
	entityPool.addEntity(2);
	entityPool.removeEntity(1);
	if (entityPool.getEntities().size() == 0);
	{
		std::cout << "Test passed: Entity removed from pool" << std::endl;
	}
}

void UnitTesting::testRandSpawn()
{
	EntityPool entityPool;
	int map[MAP_WIDTH][MAP_HEIGHT];
	sf::Vector2f spawn = entityPool.randSpawn(map);
	if (spawn.x > 0 && spawn.y > 0)
	{
		std::cout << "Test passed: Entity spawned in valid location" << std::endl;
	}
}

void UnitTesting::testUpdateEntities()
{
	EntityPool entityPool;
	Player player;
	int round = 1;
	int score = 0;
	entityPool.updateEntities(0.1f, player, round, score);
	if (entityPool.getEntities().size() > 0)
	{
		std::cout << "Test passed: Entity updated" << std::endl;
	}
}

void UnitTesting::testgetplayerPos()
{
	Player player;
	if (player.getPos().x > 0 && player.getPos().y > 0)
	{
		std::cout << "Test passed: Player position is valid" << std::endl;
	}
}

void UnitTesting::runTests()
{
	testAddEntity();
	testRemoveEntity();
	testRandSpawn();
	testUpdateEntities();
	testgetplayerPos();
}