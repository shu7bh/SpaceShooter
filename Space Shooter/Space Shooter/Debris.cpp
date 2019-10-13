#include "Debris.h"
#include "Global.h"
#include <random>//	* For having random values
#include <ctime>//	* For having time as the seed value for randomly generating values

Debris::Debris(char symbol, float speed, int health, int attack, int score)
	: Entity(2, 0, symbol, speed), health(health), attack(attack), score(score)
{
	y = newDeb();// Finds the y coordinate for the debris
	game::field[x][y] = symbol;// The debris is created on the screen
}

Debris::Debris()
	: Entity()
{
	DebType D = newDebType();// Here the deb type is found for the debris
	symbol = D.symbol, speed = D.speed, health = D.health, attack = D.attack, score = D.score;

	y = newDeb();// Finds the y coordinate for the debris
	game::field[x][y] = symbol;// The debris is created on the screen
}

Debris::Debris(int health, int attack, char symbol, float speed, int score)//This constructor for 
	: Entity(2, 0, symbol, speed), health(health), attack(attack), score(score) {}//creating templated type debris

int Debris::newDeb()// Function provides the y-coordinate for the debris
{
	static std::default_random_engine random(static_cast<unsigned int>(time(NULL)));
	static std::uniform_int_distribution<int> range(2, game::field.front().size() - 2);//Poss range
	int val;
	do
		val = range(random);
	while (game::field[2][val] != game::free);// Checks whether the coordinate is free
	return val;
}

Debris::DebType Debris::newDebType()// Function which finds the appropriate debris type
{
	static std::default_random_engine random(static_cast<unsigned int>(time(NULL)));
	static std::uniform_int_distribution<int> range(0, 1000);

	int num = range(random);
	DebType D;
	std::string name;

	if (num < 500) {// For Common Debris type, to have more no. of common debris
		name = "Common";
		D.attack = debris::types.at(name)->attack;
		D.health = debris::types.at(name)->health;
		D.symbol = debris::types.at(name)->symbol;
		D.speed = debris::types.at(name)->speed;
		D.score = debris::types.at(name)->score;
	}
	else if (num < 750) {// For Rare Debris type. Lesser freq than Common but more than Legendary
		name = "Rare";
		D.attack = debris::types.at(name)->attack;
		D.health = debris::types.at(name)->health;
		D.symbol = debris::types.at(name)->symbol;
		D.speed = debris::types.at(name)->speed;
		D.score = debris::types.at(name)->score;
	}
	else {// For Legendary Debris type. Lowest frequency of all the debris types
		name = "Legendary";
		D.attack = debris::types.at(name)->attack;
		D.health = debris::types.at(name)->health;
		D.symbol = debris::types.at(name)->symbol;
		D.speed = debris::types.at(name)->speed;
		D.score = debris::types.at(name)->score;
	}

	return D;
}

bool Debris::fire()// Function which checks whether the bullet is fired or not
{
	static std::default_random_engine random(static_cast<unsigned int>(time(NULL)));
	static std::uniform_real_distribution<float> range(0, 1.0f);

	if (0.05f > range(random))// A small chance 1 in 10 the bullet will be shot
		return true;
	return false;
}

#define Bul(name)\
	B.attack = fire::types.at(name)->getAttack(),\
	B.speed = fire::types.at(name)->getSpeed(),\
	B.symbol = fire::types.at(name)->getSymbol();

Debris::BulType Debris::newBulType()
{
	BulType B;

	static std::default_random_engine random(static_cast<unsigned int>(time(NULL)));
	static std::uniform_int_distribution<int> range(0, 1000);

	auto val = range(random);

	if (attack == debris::types.at("Common")->attack)
		Bul("Pistol")
	else if (attack == debris::types.at("Rare")->attack)
		if (val < 667)
			Bul("Pistol")
		else
			Bul("Grenade")
	else
		if (val < 333)
			Bul("Pistol")
		else if (val < 667)
			Bul("Grenade")
		else
			Bul("Missile");

	return B;
}

bool Debris::move()
{
	if (health <= 0) {//		* If the debris is already destroyed -- in terms of health -- by the
		game::pscore += score;//* bullet. The player scores will increase
		return false;//			* The bullet returns false and will be destroyed
	}
	if (fire()) {
		BulType type = newBulType();
		bullet.push_back(std::unique_ptr<Fire>(new Fire(x, y, type.symbol, type.speed, type.attack, static_cast<char>(game::dir::down))));
	}

	for (int i = 0; i < bullet.size(); i++)
		if (!bullet[i]->move())
			bullet.erase(std::begin(bullet) + i--);

	game::field[x][y] = symbol;

	static float add = 0;//	* A variable which will be adding the speed and when it reaches a
	add += speed;//			* integer type, the debris will move, and 'add' will decrease again
	for (int i = 0; i < floor(add); add--)
		if (x == game::field.size() - 2)// If the debris reaches the end, it will destroy
			return false;
		else if (game::field[x + 1][y] == game::free)// If the next pos is empty, the debris moves
			std::swap(game::field[x + 1][y], game::field[x][y]), x++;
		else if (game::field[x + 1][y] == game::psymbol)//	* If the player is at the next pos
			game::phealth -= attack;//						* the players health will decrease
		else
			break;
	return true;
}

Debris::~Debris()
{
	if (y != 0)//						 * This is only so that nothing happens for the templated 
		game::field[x][y] = game::free;// version of the debris and the only 'actual' debris destroy
}