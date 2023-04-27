#pragma once
#include "Header.h"
#include "Player.h"
#include "Raycast.h"
#include "EntityPool.h"
#include "Entity.h"
#include "Entity_1.h"
#include "Gun.h"
#include "TcpClient.hpp"




class UnitTesting
{
	
private:
	void testAddEntity();
	void testRemoveEntity();
	void testRandSpawn();
	void testUpdateEntities();
	void testgetplayerPos();

	

public:
	void runTests();
		

};

