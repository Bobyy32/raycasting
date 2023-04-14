#include "Player.h"

Player::Player()
{
	//inzialize player object to a rectangle shape with size 15x15 and color green and set origin to the center of the shape and set position to 400x300 on the window 
	this->shape.setSize(sf::Vector2f(15, 15));
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setOrigin(sf::Vector2f(15 / 2, 15 / 2));
	this->shape.setPosition(sf::Vector2f(x, y));
}

void Player::update(float d_Time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->shape.rotate(-250.f * d_Time); // Rotate left

		angle = this->shape.getRotation();
		if (angle < 0) {
			angle += 2 * PI;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->shape.rotate(250.f * d_Time); // Rotate right

		angle = this->shape.getRotation();
		if (angle > 2 * PI) {
			angle -= 2 * PI;
		}
	}

	// Update direction line based on the shape's rotation
	dx = cos(angle * PI / 180) * 5;
	dy = sin(angle * PI / 180) * 5;

	//object rotation
	sf::Vector2f direction = sf::Vector2f(std::cos(this->shape.getRotation() * PI / 180.f), std::sin(this->shape.getRotation() * PI / 180.f));
	float speed = 250.f;

	//object move forward and backward
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->shape.move(direction * -250.f * d_Time);

		x += dx;
		y += dy;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->shape.move(direction * 250.f * d_Time);

		x -= dx;
		y -= dy;
	}

	//update position
	x = this->shape.getPosition().x;
	y = this->shape.getPosition().y;
}

void Player::draw(sf::RenderTarget& target)
{
	target.draw(this->shape);


	// Draw direction line for the player
	sf::VertexArray directionLine(sf::Lines, 2);
	directionLine[0].position = sf::Vector2f(x, y);
	directionLine[1].position = sf::Vector2f(x - dx * 25, y - dy * 25);
	directionLine[0].color = sf::Color::Blue;
	directionLine[1].color = sf::Color::Blue;
	
	target.draw(directionLine);

}