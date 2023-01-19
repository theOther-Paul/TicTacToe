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
	void ShowRules()
	{
		cout << "This is an interpretation of the Classic TicTacToe game, where 2 players duel in a 4x4 square matrix.\n The goal of tic-tac-toe is to be the first player to get three in a row on a 3-by-3 grid or four in a row in a 4-by-4 grid. \n To start, one player draws a board, creating a grid of squares, usually 3 - by - 3 or 4 - by - 4. \n In a 3-by-3 grid game, the player who is playing 'X' always goes firsmenu. Players alternate placing Xs and Os on the board until either player has three in a row, horizontally, vertically, or diagonally or until all squares on the grid are filled. \n If a player is able to draw three Xs or three Os in a row, then that player wins. If all squares are filled and neither player has made a complete row of Xs or Os, then the game is a draw.";
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
		menu.add("PH");
		menu.endOfRow();
		menu.add("5");
		menu.add("Exit");
		menu.endOfRow();

		menu.setAlignment(2, TextTable::Alignment::RIGHT);
		cout << menu;
	}
};

// function declaration
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
	TitleDrop();
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
			cout << "work in progress" << endl;
			//to be implemented ofter the X variant
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
	return 0;
}