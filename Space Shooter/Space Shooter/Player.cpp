#include "Player.h"
#include <algorithm>
#include <conio.h>

Player::Player(int x, int y, char symbol, float speed, game::dir dir, int id)
	: Entity(x, y, symbol, speed), dir(dir), id(id)
{
	game::field[x][y] = symbol;// The player is created on the field
}

#define isfree(change)\
	if (game::field[x][y + change] == game::free)\
		std::swap(game::field[x][y], game::field[x][y + change]), y += change//A macro for clarity

bool Player::move()
{
	if (game::phealth <= 0)// If the player has lost, health <= 0, the player is destroyed
		return false;

	for (int i = 0; i < speed; i++)
		switch (dir)
		{
		case game::dir::left: isfree(-1);// The player moves left if coordinates are free
			break;
		case game::dir::right: isfree(1);// The player moves right if coordinates are free
			break;
		default:
			break;
		}
	for (int i = 0; i < bullet.size(); i++)//			* To move the bullets
		if (!bullet[i]->move())//						* True - Bullet should be destroyed
			bullet.erase(std::begin(bullet) + i), i--;//* Bullet is destroyed

	game::field[x][y] = symbol;// Since, when we create a new bullet, we give the coordinates \
	of the bullet the same as that of the player. So For an instant the player disappers from the \
	screen and the bullet is in its position. Not seen on the screen but happens. \
	After all the bullets move, the player regains itself in this statement
	return true;
}

void Player::input()// To get the user input 
{
	game::dir in = static_cast<game::dir> (tolower(_getch()));
	switch (in)
	{
	case game::dir::free:// Situation where the player wants to fire a bullet
		bullet.push_back(std::unique_ptr<Fire>(new Fire(x, y, fire::types.at("Hand Gun")->getSymbol(), fire::types.at("Hand Gun")->getSpeed(), fire::types.at("Hand Gun")->getAttack(), static_cast<char>(game::dir::up))));// Bullet charact
	case game::dir::left://		* For all other directions
	case game::dir::right://	* the dir will be equal to input
		dir = in;
		break;
	default:
		dir = game::dir::free;
		break;
	}
}
