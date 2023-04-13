#ifndef HEADER_H
#define HEADER_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include <iostream>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define PI 3.14159265


typedef struct position
{
	float x, y, dx, dy;
}Position;



#endif