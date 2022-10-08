// #pragma once

#include <bits/stdc++.h>
#include <Windows.h>
#include <fstream>
#include "TextTable.h"
#include <vector>

using namespace std;

// global variables
vector<string> boardValues(10);
//***************************************************************************************************************************************************************************************
//										Design sheet
// create the environment, in this case, the board with input placeholders
// create a menu and ASCII art for the beginning of the game, end of the game, win, lose and draw screen
// create a main menu with several options
// create a function that draws the board; [x]
// function that updates the board;
// create a player choice for the player to choose between player 1 and player 2, and beginning the game according to the game rules: x starts first and 0 starts second
// create a function that prints the rules
// the main loop will be the player that enters a value between 0 and 8 and the symbol will be printed in the placeholder, followed by the precomputed move, until the board is filled
//***************************************************************************************************************************************************************************************

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

void FillBoard(vector<string> &boardValues, string value)
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

void UpdateBoard(vector<string> &boardValues, int position, string value)
{
	for (int i = 0; i <= boardValues.size() - 1; i++)
	{
		if (i == position)
		{
			boardValues[i - 1] = value;
		}
	}
}

void ShowRules()
{
}

void BeginPlay()
{
	TitleDrop();
	Thread::Sleep(1000);
	system("cls");
	FillBoard(boardValues, " ");
	DisplayBoardWpHolders(boardValues);
	cout << "Choose your symbol: ";
	do
	{
		char uc;
		cin >> uc;
		uc = uc - 32;
		if (uc == 'X')
		{
			cout << "You will move first!" << endl;
			while (True)
			{
				int PlayerPosition;
				cout << "Your move: ";
				cin >> PlayerPosition;
				UpdateBoard(boardValues, PlayerPosition, " X ");
				DisplayBoardWpHolders(boardValues);
			}
		}
		else if (uc == 'O')
		{
		}
	} while (uc != 'X' || uc != 'O');
}

// main function and testing ground
int main()
{
}