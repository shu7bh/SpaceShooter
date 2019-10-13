#pragma once
class Entity
{
protected:
	int x, y;
	char symbol;
	float speed;

public:
	Entity(int x = 2, int y = 0, char symbol = ':', float speed = 1);
	virtual bool move() = 0;
};

