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
#include "Entity_2.h"

Entity_2::Entity_2()
{
	this->name = "Entity_2";
	this->position = sf::Vector2f(5.0f, 5.0f);
	this->sprite.setPosition(this->position);
	this->texture.loadFromFile("entities/Entity_2.png");
	this->sprite.setTexture(this->texture);
}

Entity_2::Entity_2(sf::Vector2f& pos) : Entity(pos)
{
	this->name = "Entity_2";
	this->position = pos;
	this->speed = 20.0f;
	this->sprite.setPosition(this->position);
	this->texture.loadFromFile("entities/Entity_2.png");
	this->sprite.setTexture(this->texture);
}

Entity_2::~Entity_2()
{
}

void Entity_2::update(const float& d_Time, const Player& player)
{
	followPlayer(player, d_Time);
}