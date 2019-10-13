#pragma once
#include "Entity.h"

class Fire:
	public Entity
{
private:
	int attack;
	char dir;
	bool destroy = false;
public:
	Fire(int, int, char, float, int, char);

	Fire(char, float, int);

	bool move() override;

	int getAttack() const { return attack; }
	int getSymbol() const { return symbol; }
	int getSpeed() const { return speed; }

	~Fire();
};