#pragma once
#include "Entity.h"
#include "Global.h"
#include "Fire.h"
#include <memory>

class Player :
	public Entity
{
private:
	game::dir dir;
	int id;
public:
	std::vector <std::unique_ptr<Fire>> bullet;

public:
	Player(int, int, char, float, game::dir, int);

	bool move() override;
	void input();

public:
	char getSymbol() const { return symbol; }
	void del() { bullet.clear(); game::field[x][y] = game::free; }
	int getId() const { return id; }
};