#pragma once
#include "Header.h"
#include "Player.h"
#include "Entity.h"
#include "EntityPool.h"

class Projectile
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f position;
	sf::Vector2f direction;
	float speed;
	//float damage;

public:
	Projectile(sf::Vector2f playerPos, sf::Vector2f direction);
	~Projectile();

	void update(const float& d_Time);

	sf::Sprite getSprite() const{ return this->sprite; }
	sf::Vector2f getPos()  const{ return this->position; }

	bool checkCollision(const Entity& entity, int map[][MAP_HEIGHT]);

};

