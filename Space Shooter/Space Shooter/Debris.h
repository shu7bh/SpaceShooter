#pragma once
#include "Entity.h"
#include "Fire.h"
#include <vector>
#include <memory>

class Debris :
	public Entity
{
private:
	int health, attack, score;
	std::vector<std::unique_ptr<Fire>> bullet;

public:
	struct DebType{
		char symbol;
		float speed;
		int health, attack, score;
	};

	struct BulType {
		char symbol;
		float speed;
		int attack;
	};

private:

	static int newDeb();
	static DebType newDebType();
	static bool fire();
	BulType newBulType();

public:
	Debris(char, float, int, int, int);

	Debris();

	Debris(int, int, char, float, int); // For creating template types. So for having a different\ constructor definition for all the same variable, I have changed the ordere of the variables

	bool move() override;

	char getSymbol() const { return symbol; }
	int getHealth() const { return health; }
	void setHealth(int health) { this->health = health; }
	int getx() const { return x; }
	int gety() const { return y; }
	int getScore() const { return score; }

	~Debris();
};