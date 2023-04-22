#include "Entity.h"

Entity::Entity()
{
	this->position = sf::Vector2f(5.0f, 5.0f);
	this->speed = 1.0f;
	sf::Texture texture;
	texture.loadFromFile("Entity_1.png");
	this->sprite.setTexture(texture);
}

Entity::Entity(sf::Vector2f& pos)
{
	this->position = pos;
}

Entity::~Entity()
{

}
