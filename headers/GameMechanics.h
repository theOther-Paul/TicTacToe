#include <Windows.h>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <cctype>
#include <random>
#include <algorithm>
#include "GameGraphics.h"
#include <string>

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

int max_of_two(int a, int b) { return a > b ? a : b; }

int max_of_two_bool(int a, int b) { return a > b ? true : false; }

template <typename T>
bool checkLegal(int position, T playerSymbol)
{
    if (position < 0 || position >= boardValues.size())
        return false; // Out of bounds check

    if (boardValues[position] == " ")
        return true; // Empty position is valid

    return false; // Any other case is invalid
}

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
        cout << "Gathering results" << endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        cout << "P1 roll is : " << rollOne << endl;
        cout << "P2 roll is : " << rollTwo << endl;

        if (rollOne == rollTwo)
        {
            DiceRoll();
        }

        return max_of_two_bool(rollOne, rollTwo);
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
        fill(boardValues.begin(), boardValues.end(), value);
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
    const uint32_t seed = os_seed();
    std::mt19937 generator(seed); // Using std::mt19937 as the random number engine
    std::uniform_int_distribution<int> distribute(0, boardValues.size() - 1); // Adjust distribution to board size

    cout << endl;
    cout << "CPU will now move";
    cout << endl;

    int position;
    bool validMove = false;
    while (!validMove)
    {
        position = distribute(generator); // Generate a random position
        if (checkLegal(position, machineSymbol))
        {
            validMove = true;
        }
    }

    cout << "Thinking..." << endl;
    cout << "[";
    for (int i = 0; i <= 6; i++)
    {
        cout << "===";
        int rsm = RandomSleepingMachine(500, 3000);
        std::this_thread::sleep_for(std::chrono::milliseconds(rsm));
    }
    cout << "]" << endl;

    UpdateBoard(boardValues, position, machineSymbol);
    DisplayBoardWPHolders(boardValues);
    }

protected:
    bool hasConsecutiveChar(const std::vector<std::string>& boardValues, const std::string& played_char, size_t position1, size_t position2, size_t position3)
{
    return (boardValues[position1] == played_char &&
            boardValues[position2] == played_char &&
            boardValues[position3] == played_char);
}

    void GameOver()
    {
        
    }

    bool CheckWinner(const std::vector<std::string>& boardValues, const std::string& played_char)
    {
        // Check rows
        if (hasConsecutiveChar(boardValues, played_char, 0, 1, 2) || 
            hasConsecutiveChar(boardValues, played_char, 3, 4, 5) || 
            hasConsecutiveChar(boardValues, played_char, 6, 7, 8))
            return true;

        // Check columns
        if (hasConsecutiveChar(boardValues, played_char, 0, 3, 6) || 
            hasConsecutiveChar(boardValues, played_char, 1, 4, 7) || 
            hasConsecutiveChar(boardValues, played_char, 2, 5, 8))
            return true;

        // Check diagonals
        if (hasConsecutiveChar(boardValues, played_char, 0, 4, 8) || 
            hasConsecutiveChar(boardValues, played_char, 2, 4, 6))
            return true;

        return false;
    }

    void BeginPlay()
    {
        // GameGraphics::TitleDrop();
        // std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        // system("cls");
        FillBoard(boardValues, " ");
    cout << "To see who goes first, let's roll a dice:" << endl;

    if (DiceRoll() == true)
    {
        cout << "You will move first!" << endl;
        cout << "Choose your symbol: ";
        char uc;
        cin >> uc;
        uc = toupper(uc);  // Convert to uppercase to handle both 'x' and 'o'

        if (uc == 'X' || uc == 'O')
        {
            string playerSymbol = (uc == 'X') ? " X " : " O ";
            string machineSymbol = (uc == 'X') ? " O " : " X ";

            bool gameOngoing = true;
            while (gameOngoing)
            {
                // Player's move
                while (true)
                {
                    int PlayerPosition;
                    cout << "Your move: ";
                    cin >> PlayerPosition;
                    if (checkLegal(PlayerPosition, playerSymbol))
                    {
                        UpdateBoard(boardValues, PlayerPosition, playerSymbol);
                        DisplayBoardWPHolders(boardValues);
                        if (CheckWinner(boardValues, playerSymbol))
                        {
                            cout << "You win!" << endl;
                            gameOngoing = false;
                            break
                        }
                        break;
                    }
                    else
                    {
                        cout << "This move is invalid! Please choose another move" << endl;
                    }
                }

                if (!gameOngoing) break;

                // Machine's move
                MachineInput(machineSymbol);
                DisplayBoardWPHolders(boardValues);
                if (CheckWinner(boardValues, machineSymbol))
                {
                    cout << "Machine wins!" << endl;
                    gameOngoing = false;
                }
            }
        }
        else
        {
            cout << "Invalid symbol! Please restart the game and choose either 'X' or 'O'." << endl;
        }
    }
    else
    {
        cout << "Dice roll indicates the machine goes first!" << endl;
        // Similar logic for when the machine starts first
    }

        DisplayBoardWPHolders(boardValues);
    }
};