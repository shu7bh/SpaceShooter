#pragma once
#include <vector>
#include <string>
#include "Debris.h"
#include <memory>
#include <map>

namespace game {
	extern std::vector<std::string> field;
	extern std::vector<std::unique_ptr<Debris>> debris;
	const char free = ' ';
	enum class dir {
		left = 'a',
		right = 'd',
		free = ' ',
		up = 'w',
		down = 's'
	};
	extern int phealth, pscore;
	const char psymbol = '^';
	void display(std::string);
	void init();
}

namespace debris {
	const std::map<std::string, std::unique_ptr<Debris>> types = [] {
		std::map<std::string, std::unique_ptr<Debris>> temp;

		temp.insert(std::make_pair<std::string, std::unique_ptr<Debris>>("Common", std::unique_ptr<Debris>(new Debris(50, 20, 'o', 1.0f, 1))));

		temp.insert(std::make_pair<std::string, std::unique_ptr<Debris>>("Rare", std::unique_ptr<Debris>(new Debris(100, 50, 'v', 0.5f, 2))));

		temp.insert(std::make_pair<std::string, std::unique_ptr<Debris>>("Legendary", std::unique_ptr<Debris>(new Debris(200, 100, '*', 0.25f, 5))));

		return temp;
	}();
}

namespace fire {
	const std::map<std::string, std::unique_ptr<Fire>> types = [] {
		std::map <std::string, std::unique_ptr<Fire>> temp;

		temp.insert(std::make_pair<std::string, std::unique_ptr<Fire>>("Hand Gun", std::unique_ptr<Fire>(new Fire('`', 2.5f, 150))));

		temp.insert(std::make_pair<std::string, std::unique_ptr<Fire>>("Pistol", std::unique_ptr<Fire>(new Fire('.', 2.0f, 100))));

		temp.insert(std::make_pair<std::string, std::unique_ptr<Fire>>("Grenade", std::unique_ptr<Fire>(new Fire('+', 3.0f, 150))));

		temp.insert(std::make_pair<std::string, std::unique_ptr<Fire>>("Missile", std::unique_ptr<Fire>(new Fire(':', 4.0f, 300))));

		return temp;
	}();
}