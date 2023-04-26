#include "Projectile.h"


Projectile::Projectile(sf::Vector2f playerPos, sf::Vector2f direction)
{
	this->speed = 200.0f;
	this->texture.loadFromFile("entities/Projectile_1.png");
	this->sprite.setTexture(this->texture);
	this->position = playerPos;
	this->direction = direction;
}

Projectile::~Projectile()
{
}

void Projectile::update(const float& d_Time)
{
	//move the projectile in initial angle of direction
	this->position += this->direction * this->speed * d_Time;
	this->sprite.setPosition(this->position);
}

bool Projectile::checkCollision(const Entity& entity, int map[][MAP_HEIGHT])
{
    sf::Vector2f entityPos = entity.getPos();

    //distance between the projectile and the entity
    float dx = position.x - entityPos.x;
    float dy = position.y - entityPos.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    // minimum distance between the projectile and the entity
    const float collisionThreshold = 30.0f; 

    //collision with entity
    if (distance <= collisionThreshold)
    {
        std::cout << "collision with entity\n";
        return true;
    }

    //collision with world
    int mapX = static_cast<int>(position.x / TILE_SIZE);
    int mapY = static_cast<int>(position.y / TILE_SIZE);

    if (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY < MAP_HEIGHT && map[mapY][mapX] != 0)
    {
        std::cout << "collision with world\n";
        return true;
    }

    return false;
}