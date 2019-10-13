#include "Game.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

void menu();
void hideCursor();

int main() 
{
	hideCursor();
	menu();

	return 0;
}

void menu()
{
	while (true) 
	{
		std::unique_ptr<Game> game(new Game(3));//A pointer is created of Game class, 3 is the starting debris number
		game::display("Main.txt");
		std::cout << "CHOOSE YOUR OPTION: ";
		int choice;
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			game::display("Instructions.txt");
			_getch();
			break;
		case 2:
			game->run();
			game->log();//Writing the record of the current game
			break;
		case 3:
			return;
		}
	}
}

void hideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}