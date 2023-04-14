#pragma once
#include "Header.h"
#include "Player.h"


class Raycast
{
private:
	Player player;

	float rayX = 0;
	float rayY = 0;
	float xOffset = 0;
	float yOffset = 0;

	float rayAngle = 0;


public:
	Raycast(Player lplayer): player(lplayer), rayAngle(player.getAngle()){}
	void DrawRays();

};

