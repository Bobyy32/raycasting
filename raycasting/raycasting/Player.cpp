#include "Player.h"

Player::Player()
{
	this->shape.setSize(sf::Vector2f(15, 15));
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setOrigin(sf::Vector2f(15 / 2, 15 / 2));
	this->shape.setPosition(sf::Vector2f(400, 300));
}

void Player::update(float d_Time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->shape.rotate(-250.f * d_Time); // rotate left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->shape.rotate(250.f * d_Time); // rotate right

	sf::Vector2f direction = sf::Vector2f(std::cos(this->shape.getRotation() * PI / 180.f), std::sin(this->shape.getRotation() * PI / 180.f));
	float speed = 250.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->shape.move(direction * -250.f * d_Time);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->shape.move(direction * 250.f * d_Time);

	pos.x = this->shape.getPosition().x;
	pos.y = this->shape.getPosition().y;
}

void Player::draw(sf::RenderTarget& target)
{
	target.draw(this->shape);
}

