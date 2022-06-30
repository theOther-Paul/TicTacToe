#include <iostream>
#include <Windows.h>

#define LOG(x) std::cout << x << std::endl
#define log(x) std::cout << x

char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

void TitleDrop()
{
	system("color a");
	LOG(" __      __         .__                                         __");
	LOG("/  \    /  \  ____  |  |    ____   ____    _____    ____      _/  |_  ____                                                                                  ");
	LOG("\   \/\/   /_/ __ \ |  |  _/ ___\ /  _ \  /     \ _/ __ \     \   __\/  _ \                                                                                 ");
	LOG(" \        / \  ___/ |  |__\  \___(  <_> )|  Y Y  \\  ___/      |  | (  <_> )                                                                                ");
	LOG("  \__/\  /   \___  >|____/ \___  >\____/ |__|_|  / \___  >     |__|  \____/                                                                                 ");
	LOG("       \/        \/            \/              \/      \/                                                                                                   ");
	LOG("                                                                                                                                                            ");
	LOG("                                                                                    ___________.__       ___________              ___________               ");
	LOG("                                                                                    \__    ___/|__|  ____\__    ___/_____     ____\__    ___/____    ____   ");
	LOG("                                                                                      |    |   |  |_/ ___\ |    |   \__  \  _/ ___\ |    |  /  _ \ _/ __ \  ");
	LOG("                                                                                      |    |   |  |\  \___ |    |    / __ \_\  \___ |    | (  <_> )\  ___/  ");
	LOG("                                                                                      |____|   |__| \___  >|____|   (____  / \___  >|____|  \____/  \___  > ");
	LOG("                                                                                                        \/               \/      \/                     \/  ");
	LOG("                                                                                                                                                            ");
	Sleep(3);
}

void DrawBoard(char choice)
{
	std::cout << "     |     |     \n";
	std::cout << "  " << board[0][0] << "  | " << board[0][1] << " "
			  << "  |  " << board[0][2] << "\n";
	std::cout << "_____|_____|_____\n";
	std::cout << "     |     |     \n";
	std::cout << "  " << board[1][0] << "  | " << board[1][1] << " "
			  << "  |  " << board[1][2] << " \n";
	std::cout << "_____|_____|_____\n";
	std::cout << "     |     |     \n";
	std::cout << "  " << board[2][0] << "  | " << board[2][1] << " "
			  << "  |  " << board[2][2] << " \n";
	std::cout << "     |     |     \n";
}

int main()
{
	TitleDrop();
	char PlayerChoice;
	do
	{
		LOG("Please choose a sign. (X or 0)");
		std::cin >> PlayerChoice;
		if (PlayerChoice == 'X' || PlayerChoice == 'x')
		{
			system("cls");
			DrawBoard(PlayerChoice);
		}
		else if (PlayerChoice == '0')
		{
			system("cls");
			DrawBoard(PlayerChoice);
		}
	} while (PlayerChoice != 'X' || PlayerChoice != '0');
}