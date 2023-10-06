// #pragma once

#include <Windows.h>
#include <fstream>
#include "TextTable.h"
#include <vector>
#include <thread>
#include <chrono>
#include <cctype>
#include <random>

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::string;
using std::thread;
using std::vector;
using u32 = uint_least32_t;
using engine = std::mt19937;

// global variables
vector<string> boardValues(10);
bool locked = false;
//***************************************************************************************************************************************************************************************
//										Design sheet
// create the environment, in this case, the board with input placeholders [x]
// create a menu [x]
// create ASCII art for the beginning of the game [x], end of the game, win, lose and draw screen
// create a main menu with several options [x]
// create a function that draws the board; [x]
// function that updates the board; [x]
// create a player choice for the player to choose between player 1 and player 2, and beginning the game according to the game rules: x starts first and 0 starts second [x]
// create a function that prints the rules [x]
// the main loop will be the player that enters a value between 0 and 8 and the symbol will be printed in the placeholder, followed by the precomputed move, until the board is filled
//***************************************************************************************************************************************************************************************

// graphics structure
class GameGraphics
{
protected:
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

	/**
	 * The function "p1win" reads and prints the content of a file containing ASCII art representing a
	 * victory message for player 1.
	 */
	void p1win()
	{
		fstream p1("ascii_art/P1won.txt");
		if (!p1)
		{
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
			else
				cout << "Error";
		}
	}

	void p2win()
	{
		fstream p2("ascii_art/p2won.txt");
		if (!p2)
		{
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
			else
				cout << "Error";
		}
	}
};

// game mechanics implementation
/* The GameMechanics class contains functions for simulating dice rolls, filling and updating a game
board, displaying the board, and handling player and machine inputs in a game. */
class GameMechanics : protected GameGraphics
{
protected:
	/**
	 * The function "DiceRoll" simulates rolling two dice and determines which player will go first based
	 * on the results.
	 */
	int DiceRoll()
	{
		int max = 6;
		srand(time(0));
		cout << "The dice is rolling" << endl;
		cout << endl;
		auto rollOne = rand() % max;
		auto rollTwo = rand() % max;

		cout << endl;
		cout << "Gethering results" << endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
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
				return rollOne;
			}

			else
			{
				cout << "P2 will go first" << endl;
				return rollTwo;
			}
		}
	}

	/**
	 * The function FillBoard fills a vector of strings with a specified value.
	 *
	 * @param boardValues A vector of strings representing the board values.
	 * @param value The value is a string that will be used to fill the elements of the boardValues vector.
	 *
	 * @return the result of the `fill` function, which is not specified in the given code.
	 */
	void FillBoard(vector<string> &boardValues, string value)
	{
		return (fill(boardValues.begin(), boardValues.end() - 1, value));
	}

	/**
	 * The function `DisplayBoardWPHolders` takes a vector of strings representing a board and displays it
	 * in a formatted table.
	 *
	 * @param boardValues A vector of strings representing the values to be displayed on the game board.
	 */
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

	/**
	 * The function `UpdateBoard` updates a specific position on a board with a given value.
	 *
	 * @param boardValues A vector of strings representing the current state of the board.
	 * @param position The position parameter is an integer that represents the index of the element in
	 * the boardValues vector that needs to be updated.
	 * @param value The value parameter is the string value that you want to update the board with.
	 */
	void UpdateBoard(vector<string> &boardValues, int position, string value)
	{
		for (int i = 0; i < boardValues.size(); i++)
		{
			if (i == position)
			{
				boardValues[static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(i) - 1] = value;
			}
		}
	}

private:
	/**
	 * The function `MachineInput` generates a random number and uses it to update the game board with the
	 * given machine symbol, while also displaying a thinking animation.
	 *
	 * @param machineSymbol The parameter `machineSymbol` is a string that represents the symbol used by
	 * the machine player in a game. It is used to update the game board with the machine player's move.
	 */
	int RandomSleepingMachine(int minDur, int maxDur)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_int_distribution<int> distribution(minDur, maxDur);

		int sleepDuration = distribution(gen);

		return sleepDuration;
	}
	void MachineInput(string machineSymbol)
	{
		std::random_device os_seed;
		const u32 seed = os_seed();
		engine generator(seed);
		std::uniform_int_distribution<u32> distribute(0, 8);

		cout << "CPU will now move";

	generateInput:
		for (int repetition = 0; repetition < 1; ++repetition)
		{
			int position = distribute(generator); // Generate a random position
			UpdateBoard(boardValues, position, machineSymbol);
			cout << endl;
			cout << "Thinking..." << endl;
			cout << "[";
			for (int i = 0; i <= 6; i++)
			{
				cout << "===";
				int rsm = RandomSleepingMachine(500, 3000);
				std::this_thread::sleep_for(std::chrono::milliseconds(rsm));
			}
			cout << "]" << endl;
			DisplayBoardWPHolders(boardValues);
		}
	}
	void CheckWinner()
	{
	}

protected:
	void BeginPlay()
	{
		// GameGraphics::TitleDrop();
		// std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		// system("cls");
		FillBoard(boardValues, " ");
		cout << "To see who goes first, let's roll a dice:" << endl;
		int to_start = DiceRoll();

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
					if (boardValues[PlayerPosition] == " ")
					{
						// locked = true;

						UpdateBoard(boardValues, PlayerPosition, " X ");
						DisplayBoardWPHolders(boardValues);
						MachineInput("O");
					}
				}
			}

			else if (uc == 'O')
			{
				cout << "*********************" << endl;
				cout << "Work in progress..." << endl;
				cout << "*********************" << endl;
				// to be implemented after the X variant
			}
		} while (uc != 'X' || uc != 'O');

		DisplayBoardWPHolders(boardValues);
	}
};

/* The MenuClass is a class that displays a menu and allows the user to choose different options. */
class MenuClass : protected GameMechanics
{
public:
	/**
	 * The function ShowRules reads and displays the content of a file named "rules.txt" in ASCII art
	 * format.
	 */
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

	void DisplayMenu()
	{
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
		menu.add("Board Skins"); // work in progress after finishing the main game loop
		menu.endOfRow();
		menu.add("5");
		menu.add("Exit");
		menu.endOfRow();

		menu.setAlignment(2, TextTable::Alignment::RIGHT);
		cout << menu;
	}

	void OptionChoice()
	{
		unsigned int PlayerChoice;
		do
		{
			cout << "Awaiting your choice: ";
			cin >> PlayerChoice;
			if (PlayerChoice < 1 && PlayerChoice > 5)
				cout << "Invalid choice! Please try again" << endl;
			else
			{
				switch (PlayerChoice)
				{
				case 1:
					system("cls");
					MenuClass::ShowRules();
					cout << "\n You will be returned to the main menu in 5 seconds";
					std::this_thread::sleep_for(std::chrono::milliseconds(5000));
					this->DisplayMenu();
					OptionChoice();
				case 2:
					cout << "This section is still a work in progress!";
					cout << "\n You will be returned to the main menu";
					DisplayMenu();
					OptionChoice();
				case 3:
					GameMechanics::BeginPlay();
				case 4:
					cout << "This section is still a work in progress!";
					cout << "\n You will be returned to the main menu";
					DisplayMenu();
					OptionChoice();
				default:
					break;
				}
			}
		} while (PlayerChoice < 1 || PlayerChoice > 5);
	}
};

int max_of_two(int a, int b) { return a > b ? a : b; }

int max_of_two_bool(int a, int b) { return a > b ? true : false; }

// testing area
int DiceRoll(string firstPlayer, string secondPlayer){}
{
	int max = 6;
	srand(time(0));
	cout << "The dice is rolling" << endl;
	cout << endl;
	auto rollOne = rand() % max;
	auto rollTwo = rand() % max;

	cout << endl;
	cout << "Gethering results" << endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	cout << "P1 roll is : " << rollOne << endl;
	cout << "P2 roll is : " << rollTwo << endl;

	if (rollOne == rollTwo)
	{
		DiceRoll();
	}

	else
	{
		return max_of_two_bool(rollOne, rollTwo);
	}
}

// main function and testing ground
int main()
{
	// MenuClass MainMenu;
	// MainMenu.DisplayMenu();
	// MainMenu.OptionChoice();
	cout << DiceRoll();
	return 0;
}