#include "Fire.h"
#include "Global.h"
#include <algorithm>//	* For swap()

Fire::Fire(int x, int y, char symbol, float speed, int attack, char dir)
	: Entity(x, y, symbol, speed), attack(attack), dir(dir)
{
	game::field[x][y] = symbol;// The bullet is created on the game::field
}

Fire::Fire(char symbol, float speed, int attack)//		* For the creation of Bullet
	: Entity(INT_MAX, INT_MAX, symbol, speed), attack(attack), dir(static_cast<char>(game::dir::free)) {}//* Templates

bool Fire::move()
{
	if (destroy)
		return false;

	for (int i = 0; i < speed; i++)
		if (dir == static_cast<char>(game::dir::up))
			if (x == 0)//		* If the bullet has reached the top of the screen
				return false;// * The bullet will be destroyed
			else if (game::field[x - 1][y] == game::free)//	* If the next place is free the bullet
				std::swap(game::field[x][y], game::field[x - 1][y]), x--;//* will move there
			else if (game::field[x - 1][y] == fire::types.at("Pistol")->symbol || game::field[x - 1][y] == fire::types.at("Grenade")->symbol || game::field[x - 1][y] == fire::types.at("Missile")->symbol)
				destroy = true;
			else {
				for (auto& deb : game::debris)//				* If the bullet encounters a debris
					if (x - 1 == deb->getx() && y == deb->gety())//*Checked by matching coordinates
						deb->setHealth(deb->getHealth() - attack);//* The debris health decreases
				return false;//		* The bullet will be destroyed
			}
		else
			if (x == game::field.size() - 2)
				return false;
			else if (game::field[x + 1][y] == game::free)
				std::swap(game::field[x][y], game::field[x + 1][y]), x++;
			else if (game::field[x + 1][y] == fire::types.at("Hand Gun")->symbol)
				destroy = true;
			else if (game::field[x + 1][y] == game::psymbol) {
				game::phealth -= attack;
				return false;
			}
	return true;// The bullet moves successfully
}

Fire::~Fire()
{
	if (y != INT_MAX)// Since the templatised bullets neednot be destroyed
		game::field[x][y] = game::free;// The bullet coordinates are freed from game::field 
}
