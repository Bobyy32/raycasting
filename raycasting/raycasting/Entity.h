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
#pragma once
#include "Header.h"
#include "Player.h"


class Entity
{
protected:
	sf::Vector2f position;	//sprite position
	sf::Sprite sprite;
	sf::Texture texture;
	std::string name;

	int health;
	float speed;

public:
	Entity();
	Entity(sf::Vector2f& pos);
	virtual ~Entity();

	virtual void update(const float& d_Time, const Player& player) = 0;

	void followPlayer(const Player& player, const float& d_Time);

	sf::Vector2f getPos()const { return this->position; }
	void setPos(sf::Vector2f& pos) { this->position = pos; }

	int getHealth()const { return this->health; }
	void setHealth(int health) { this->health = health; }

	bool isDead()const { return this->health <= 0; }

	std::string getName()const { return this->name; }

	const sf::Sprite& getSprite() const { return this->sprite; }
};