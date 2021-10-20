#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "poker.h"
using namespace std;

int main(int argc, char* argv[])
{
    cout << "Poker Hands\n" <<
            "Zach Schickler\n" <<
            "10/19/2021" << endl;

    string dir = "hands.txt";
    fstream stream;
    bool debug = false, showTies = false;
    vector<vector<Card>> playerHands;

    // Case: Program ran with optional variables set.
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            // Check for flags...
            if (argv[i][0] == '-')
            {
                switch(argv[i][1])
                {
                    // Case: Specify path.
                    case 'd':
                        // Prevent bounds error by ensuring path was given after flag.
                        if (i+1 >= argc)
                        {
                            cout << "\nError: No path specified after -d" << endl;
                            return 0;
                        }
                        dir = argv[i+1];
                        break;
                    // Case: Full print out.
                    case 'p':
                        debug = true;
                        break;
                    // Case: Print ties.
                    case 't':
                        showTies = true;
                        break;
                    // Unrecognized flags continue on to print help debug, since people using unrecognized flags may need it.
                    default:
                        cout << "\nUnrecognized flag: -" << argv[i][1] << endl;
                    case 'h':
                        cout << "\nUsage:\n\n" <<
                                "-h\t\tDisplays usage information and any optional flags.\n" <<
                                "-d [dir]\tUsed to specify the path to file \"hands.txt\". Otherwise, uses default file in root directory.\n" <<
                                "-p\t\tPrints out full output of game, including each player's hand and hand ranking.\n" <<
                                "-t\t\tPrints out ties in winners list." << endl;
                        return 0;
                        break;
                }
            }
        }
    }

    // Default directory warning.
    if (dir == "hands.txt") cout << "\nWARNING: Using default directory, expecting \"hands.txt\" in root directory..." << endl;

    // File should be used for reading only.
    stream.open(dir, fstream::in);

    // Check that file exists and can be read.
    if (stream.fail())
    {
        cout << dir << " could not be opened. Is your path correct?" << endl;
        return 0;
    }

    // Time to read.
    while (!stream.eof())
    {
        string line;
        getline(stream, line);

        // Skip over empty lines or new lines to prevent malformed cards.
        if (line == "" || line == "\n" || line == "\r")
            continue;

        // Stringstream is used to split up a line into unique cards delimited by spaces.
        stringstream linestream(line);
        string cardString;
        vector<Card> hand;
        while (linestream >> cardString)
        {
            // Utilizing createCardFromString from functions.cpp to handle the dirty work of creating card object with string data.
            Card card = createCardFromString(cardString);
            hand.push_back(card);
        }

        // Once our hand is formed, we can register it as a player.
        playerHands.push_back(hand);
    }

    // Done with file.
    stream.close();

    if (debug)
    {
        cout << "\nPlayers: " << playerHands.size() << endl;
        cout << "Cards per: " << playerHands[0].size() << endl;
    }

    vector<vector<int>> playerScores;

    // Time to score all the players' hands.
    for (int i = 0; i < playerHands.size(); i++)
    {
        if (debug)
        {
            cout << "\nPlayer " << i + 1 << endl;
        }
        // Utilizing getRankFromHand from functions.cpp to get 1 score for 1 particular hand.
        // (Based on ranking from https://en.wikipedia.org/wiki/List_of_poker_hands#Two_pair).
        vector<int> playerAndScore = {i, getRankFromHand(playerHands[i], debug)};
        playerScores.push_back(playerAndScore);
    }

    // Utilizing printWinner from functions.cpp to show winners. ONLY prints to console.
    printWinner(playerScores, showTies);

    // Exit.
    return 0;
}