#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool hasConsecutiveChar(vector<string> boardValues, char played_char, size_t position1, size_t position2, size_t position3)
{
    for (const std::string &sequence : boardValues)
    {
        if (position3 < sequence.length() &&
            sequence[position1] == played_char &&
            sequence[position2] == played_char &&
            sequence[position3] == played_char)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    vector<string> bv(10, "x0xxxx000");
    if(hasConsecutiveChar(bv, '0', 6,7,8)==true){
        cout<<"Winner";
    }
}