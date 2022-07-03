#include <iostream>
#include <Windows.h>

#define LOG(x) std::cout << x << std::endl
#define log(x) std::cout << x

char board[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };

void DrawBoard()
{
	std::cout << "     |     |     \n";
	std::cout << "  " << board[0] << "  | " << board[1] << " "
		<< "  |  " << board[2] << "\n";
	std::cout << "_____|_____|_____\n";
	std::cout << "     |     |     \n";
	std::cout << "  " << board[3] << "  | " << board[4] << " "
		<< "  |  " << board[5] << " \n";
	std::cout << "_____|_____|_____\n";
	std::cout << "     |     |     \n";
	std::cout << "  " << board[6] << "  | " << board[7] << " "
		<< "  |  " << board[8] << " \n";
	std::cout << "     |     |     \n";
}

int main()
{
	char PlayerChoice;

	LOG("Please choose a sign. (X or 0)");
	std::cin >> PlayerChoice;
	if (PlayerChoice == 'X' || PlayerChoice == 'x')
	{
		LOG("You will play as Player 1");
		Sleep(5);
		system("cls");
		LOG("\nPlayer 1 [X] VS. Player 2 [0]");
		DrawBoard();

		int PlayerMove;
		std::cout << "Your move: ";
		std::cin >> PlayerMove;
		switch (PlayerMove)
		{
		case 1:
			board[0] = PlayerMove;
			DrawBoard();
			break;
		}
	}

	else
	{
		LOG("You will play as Player 2");
		system("cls");
		DrawBoard();
	}
}