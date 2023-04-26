#pragma once
#include "Header.h"
#include "Player.h"
#include "Entity.h"
#include "EntityPool.h"
#include "Projectile.h"

class Gun
{
private:
	
	std::vector<Projectile*> projectiles;

	int damage;
	int ammo;
	int magazineSize;
	bool emptyMagazine;


public:
	Gun();
	~Gun();

	void shoot(sf::Vector2f playerPos, sf::Vector2f direction);

	std::vector<Projectile*>& getProjectiles() { return projectiles; }
	
	void updateProjectiles(float d_Time, const EntityPool& entityPool);

	int getDamage()const { return this->damage; }

};

