#include "Game.h"
#include "Global.h"
#include <fstream>//	* To read and write on the file
#include <string>
#include <iostream>//	* To display the game on the console
#include <Windows.h>//	* For clearing the screen
#include <conio.h>//	* For _getch() and _kbhit()

Game::Game(float startdebnum)
	: startdebnum(startdebnum)
{
	game::init();
	std::ifstream field("Field.txt");//		*
	std::string line;//						* Reading the field from a text file and initialising  
	if (field.is_open())//					* 
		while (std::getline(field, line))//	* it to game::field, the vector where all changes happen
			game::field.push_back(line);//	*

	std::unique_ptr<Player> temp(new Player(game::field.size() - 2, game::field.front().size() / 2, game::psymbol, 1, game::dir::free, read()));
	player = std::move(temp);// A temp pointer of Player is created with the desired values, the player var gains this memory from temp
}

bool Game::run()
{
	while (true) {
		for (int i = game::debris.size(); i <= floor(startdebnum); i++)//	* Creating new debris 
			game::debris.push_back(std::unique_ptr<Debris>(new Debris));//	* after each round

		startdebnum += 0.001;//	increasing it to make game harder
		system("CLS"), display();
		Sleep(75);

		if (_kbhit())//			* If the user enters a value
			player->input();//	*
		if (!player->move())// This will return true if the player is dead, i.e. health <= 0
			break;
		for (int i = 0; i < game::debris.size(); i++)//					* Moves the debris
			if (!game::debris[i]->move())//								* If the debris is dead
				game::debris.erase(std::begin(game::debris) + i), i--;//* Destroys it
	}
	player->del();// Deletes all the information regarding to player, especially the bullets, so 
	game::debris.clear();// that later, when the game::field is destroyed, there is no problem in 
	return false;//		deallocating memory.
}
// #define Col(x) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x)
void Game::display()
{
	/*
	int i;
	std::cout << "\n\n";
	for (i = 0; i < game::field.size(); i++) {
		printf("      ");
		for (int j = 0; j < game::field[i].size(); j++) {
			if (game::field[i][j] == game::psymbol)
				Col(10);
			else if (game::field[i][j] == debris::types.at("Common")->getSymbol() ||
				game::field[i][j] == debris::types.at("Rare")->getSymbol() ||
				game::field[i][j] == debris::types.at("Legendary")->getSymbol())
				Col(2);
			else if (game::field[i][j] == bullet::types.at("Hand Gun")->getSymbol())
				Col(7);
			else if (game::field[i][j] == bullet::types.at("Pistol")->getSymbol() ||
				game::field[i][j] == bullet::types.at("Grenade")->getSymbol() ||
				game::field[i][j] == bullet::types.at("Missile")->getSymbol())
				Col(3);
			else
				Col(11);
			printf("%c", game::field[i][j]);
		}
		printf("\n");
	}

		//std::cout << game::field[i] << '\n';
	//for (auto i = std::begin(game::field); i != std::end(game::field); i++)
		//std::cout << *i << '\n';*/ 
		// Only for giving colour for the console

	for (const auto& line : game::field)
		std::cout << line << '\n';
	std::cout << "\n\n\t" << "SCORE: " << game::pscore << "\t\tHEALTH: " << game::phealth;
}

void Game::log() // After a game, records the stats
{
	std::ofstream fout("Record.txt", std::ios::out | std::ios::app);

	fout << "\n\n" << player->getId() << '\n' << game::pscore;
	fout.close();
}

int Game::read() // Reads the id, so as to give the new player an id greater than the current
{
	std::ifstream fin("Record.txt");
	
	fin.seekg(0, std::ios_base::end);
	if (!fin.tellg())//	* Trying to see if the file is empty.
		return 1;//		* In this case the first id num possible is returned
	
	fin.seekg(-2 * int(sizeof(int)), std::ios_base::cur);
	int id;
	fin >> id;
	return id + 1;
}