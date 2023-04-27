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
#include "Gun.h"

Gun::Gun()
{
    this->damage = 50;
}

Gun::~Gun()
{
}

void Gun::shoot(sf::Vector2f playerPos, sf::Vector2f direction)
{
    std::cout << "shooting\n";

    
    Projectile* newProjectile = new Projectile(playerPos, direction);
    projectiles.push_back(newProjectile);
}

void Gun::updateProjectiles(float d_Time, const EntityPool& entityPool)
{
    for (Projectile* projectile : projectiles) {
        projectile->update(d_Time);

        for (auto& entity : entityPool.getEntities())
        {
            if (projectile->checkCollision(*entity, worldMap))
            {
                entity->setHealth(entity->getHealth() - damage);
                projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
            }
        }
    }
}

