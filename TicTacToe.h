#pragma once

#include <Windows.h>
#include <fstream>
#include "TextTable.h"
#include <vector>
#include <thread>
#include <chrono>
#include <cctype>
#include <random>
#include <algorithm>
// #include "headers/GameGraphics.h"
#include "headers/GameMechanics.h"

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::string;
using std::thread;
using std::vector;
using u32 = uint_least32_t;
using engine = std::mt19937;

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