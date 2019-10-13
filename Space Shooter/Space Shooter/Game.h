#pragma once
#include "Player.h"
#include "Debris.h"
#include <vector>
#include <memory>

class Game
{
private:
	float startdebnum;
	std::unique_ptr<Player> player;
public:
	Game(float);
	bool run();
	void log();
private:
	void display();
	int read();
};