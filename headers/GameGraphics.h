#include <fstream>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::string;

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