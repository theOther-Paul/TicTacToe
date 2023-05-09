// #pragma once

#include <Windows.h>
#include <fstream>
#include "TextTable.h"
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

// global variables
vector<string> boardValues(10);
//***************************************************************************************************************************************************************************************
//										Design sheet
// create the environment, in this case, the board with input placeholders [x]
// create a menu [x]
// create ASCII art for the beginning of the game [x], end of the game, win, lose and draw screen
// create a main menu with several options
// create a function that draws the board; [x]
// function that updates the board; [x]
// create a player choice for the player to choose between player 1 and player 2, and beginning the game according to the game rules: x starts first and 0 starts second [x]
// create a function that prints the rules [x]
// the main loop will be the player that enters a value between 0 and 8 and the symbol will be printed in the placeholder, followed by the precomputed move, until the board is filled
//***************************************************************************************************************************************************************************************

//menu class implementation

class MenuClass {
public:
	static void ShowRules()
	{
		fstream rules("ascii_art/rules.txt");
		if (!rules)
		{
			cout << "No file found" << endl;
		}
		else
		{
			string content;
			if (rules.is_open())
			{
				while (rules.good())
				{
					content = rules.get();
					cout << content;
				}
				rules.close();
			}
			else
				cout << "Error";
		}
	}

	void DisplayMenu() {
		TextTable menu('-', '|', '+');
		menu.add("");
		menu.add("Choose an option");
		menu.endOfRow();
		menu.add("1");
		menu.add("Show Rules");
		menu.endOfRow();
		menu.add("2");
		menu.add("Vs. Player");
		menu.endOfRow();
		menu.add("3");
		menu.add("Vs. CPU");
		menu.endOfRow();
		menu.add("4");
		menu.add("Board Skins"); //work in progress after finishing the main game loop
		menu.endOfRow();
		menu.add("5");
		menu.add("Exit");
		menu.endOfRow();

		menu.setAlignment(2, TextTable::Alignment::RIGHT);
		cout << menu;
	}

	void OptionChoice() {
		unsigned int PlayerChoice;
		do {
			cout << "Awaiting your choice: ";
			cin >> PlayerChoice;
			if (PlayerChoice < 1 && PlayerChoice>5)
				cout << "Invalid choice! Please try again" << endl;
			else
			{
				switch (PlayerChoice)
				{
				case 1:
					system("cls");
					MenuClass::ShowRules();
				default:
					break;
				}
			}
		} while (PlayerChoice < 1 || PlayerChoice>5);
	}
};

//graphics structure
struct GameGraphics {
	void TitleDrop()
	{
		fstream TitleD("ascii_art/titleDrop.txt");
		if (!TitleD)
		{
			cout << "No file found" << endl;
		}
		else
		{
			string content;
			if (TitleD.is_open())
			{
				while (TitleD.good())
				{
					content = TitleD.get();
					cout << content;
				}
				TitleD.close();
			}
			else
				cout << "Error";
		}
	}

	void p1win() {
		fstream p1("ascii_art/P1won.txt");
		if (!p1) {
			cout << "Failed to load resource" << endl;
		}

		else
		{
			string content;
			if (p1.is_open())
			{
				while (p1.good())
				{
					content = p1.get();
					cout << content;
				}
				p1.close();
			}
			else cout << "Error";
		}
	}

	void p2win() {
		fstream p2("ascii_art/p2won.txt");
		if (!p2) {
			cout << "Failed to load resource" << endl;
		}

		else
		{
			string content;
			if (p2.is_open())
			{
				while (p2.good())
				{
					content = p2.get();
					cout << content;
				}
				p2.close();
			}
			else cout << "Error";
		}
	}
};

//function declaration
void DiceRoll()
{
	int max = 6;
	srand(time(0));
	cout << "The dice is rolling" << endl;
	cout << endl;
	auto rollOne = rand() % max;
	auto rollTwo = rand() % max;
	this_thread::sleep_for(chrono::milliseconds(3000));
	cout << "P1 roll is : " << rollOne << endl;
	cout << "P2 roll is : " << rollTwo << endl;

	if (rollOne == rollTwo)
	{
		DiceRoll();
	}

	else
	{
		if (rollOne > rollTwo)
		{
			cout << "P1 will go first" << endl;
		}

		else cout << "P2 will go first" << endl;
	}
}

void FillBoard(vector<string>& boardValues, string value)
{
	return (fill(boardValues.begin(), boardValues.end() - 1, value));
}

void DisplayBoardWPHolders(vector<string> boardValues)
{
	TextTable board('-', '|', '+');
	for (int i = 0; i < boardValues.size() - 1; i++)
	{
		board.add(boardValues[i]);
		if (i == 2 || i == 5 || i == 8)
		{
			board.endOfRow();
		}
	}
	board.setAlignment(2, TextTable::Alignment::LEFT);
	cout << board;
}

void UpdateBoard(vector<string>& boardValues, int position, string value)
{
	for (int i = 0; i <= boardValues.size() - 1; i++)
	{
		if (i == position)
		{
			boardValues[static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(i) - 1] = value;
		}
	}
}

void BeginPlay()
{
	// GameGraphics.TitleDrop();
	this_thread::sleep_for(chrono::milliseconds(3000));
	system("cls");
	FillBoard(boardValues, " ");
	cout << "To see who goes first, let's roll a dice:" << endl;
	DiceRoll();
	cout << "Choose your symbol: ";
	char uc;
	do
	{
		cin >> uc;
		uc = uc - 32;
		if (uc == 'X')
		{
			cout << "You will move first!" << endl;
			while (true)
			{
				int PlayerPosition;
				cout << "Your move: ";
				cin >> PlayerPosition;
				UpdateBoard(boardValues, PlayerPosition, " X ");
				DisplayBoardWPHolders(boardValues);
			}
		}
		else if (uc == 'O')
		{
			cout << "*********************" << endl;
			cout << "Work in progress..." << endl;
			cout << "*********************" << endl;
			//to be implemented after the X variant
		}
	} while (uc != 'X' || uc != 'O');

	DisplayBoardWPHolders(boardValues);
}

// main function and testing ground
int main()
{
	//BeginPlay();
	MenuClass MainMenu;
	MainMenu.DisplayMenu();
	//GameGraphics GG;
	//GG.p1win();
	return 0;
}