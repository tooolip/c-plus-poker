#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
    cout << "Hands Maker\n" <<
            "Zach Schickler\n" <<
            "10/19/2021" << endl;

    fstream stream;
    stream.open("hands.txt", fstream::out);

    vector<char> numbers = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'J', 'Q', 'K'};
    vector<char> suits = {'S', 'H', 'D', 'C'};

    for (int j = 0; j < 100; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            stream.put(numbers[rand() % numbers.size()]);
            stream.put(suits[rand() % suits.size()]);
            stream.put(' ');
        }
        stream.put(numbers[rand() % numbers.size()]);
        stream.put(suits[rand() % suits.size()]);
        stream.put('\n');
    }

    stream.close();

    return 0;
}