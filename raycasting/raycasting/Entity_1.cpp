#include "Entity_1.h"

Entity_1::Entity_1(sf::Vector2f& pos)
{
	this->position = pos;
	this->speed = 1.0f;
	this->sprite.setPosition(this->position);
}

Entity_1::~Entity_1()
{

}

void Entity_1::update(const float& d_Time)
{
}
