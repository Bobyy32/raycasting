/************************************************************************
* Programmer: Sean Duffy		                                        *
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
#include "Entity.h"

Entity::Entity()
{
	this->position = sf::Vector2f(5.0f, 5.0f);
	this->health = 100;
	this->speed = 20.0f;
}

Entity::Entity(sf::Vector2f& pos)
{
	this->position = pos;
	this->health = 100;
	this->speed = 20.0f;
}

Entity::~Entity()
{

}

void Entity::followPlayer(const Player& player, const float& d_Time)
{
	sf::Vector2f playerPos(player.getX(), player.getY());
	sf::Vector2f direction = playerPos - this->position;
	float length = sqrt((direction.x * direction.x) + (direction.y * direction.y));
	direction.x /= length;
	direction.y /= length;
	this->position += direction * this->speed * d_Time;
}