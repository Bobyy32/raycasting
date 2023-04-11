#include "Game.h"

void Game::initializeVariables()
{
	this->window = nullptr;
}

void Game::initializeWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Raycasting");
}

Game::Game()
{
	this->initializeVariables();
	this->initializeWindow();
}

Game::~Game()
{
	delete this->window;
}


//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}


void Game::updatePollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

//Funcitons
void Game::update()
{
	updatePollEvents();
}

void Game::render()
{
	/*
		-Clear old frame
		-Renders Game Objects
		-Display frame in window

	*/

	this->window->clear();

	//Draw game objects

	/*this->window->draw(sf::CircleShape(),);*/

	this->window->display();
}
