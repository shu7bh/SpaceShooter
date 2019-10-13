#include "Global.h"
#include <fstream>
#include <iostream>

std::vector <std::string> game::field;
std::vector<std::unique_ptr<Debris>> game::debris;

int game::phealth = 1500, game::pscore = 0;

void game::display(std::string name)
{
	system("CLS");
	std::ifstream fin(name);
	std::string line;
	std::getline(fin, line);
	std::cout << line;
	while (std::getline(fin, line))
		std::cout << '\n' << line;
}

void game::init()
{
	phealth = 1500;
	game::field.clear();
	debris.clear();
	pscore = 0;
}