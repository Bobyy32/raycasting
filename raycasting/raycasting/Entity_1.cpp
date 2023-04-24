#include "Entity_1.h"

Entity_1::Entity_1()
{
	this->name = "Entity_1";
	this->position = sf::Vector2f(5.0f, 5.0f);
	this->sprite.setPosition(this->position);
	this->texture.loadFromFile("entities/Entity_1.png");
	this->sprite.setTexture(this->texture);
}

Entity_1::Entity_1(sf::Vector2f& pos) : Entity(pos)
{
	this->name = "Entity_1";
	this->position = pos;
	this->sprite.setPosition(this->position);
	this->texture.loadFromFile("entities/Entity_1.png");
	this->sprite.setTexture(this->texture);
}

Entity_1::~Entity_1()
{

}

void Entity_1::update(const float& d_Time, const Player& player)
{
	followPlayer(player, d_Time);
}

