#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "card.h"
#include "functions.h"
using namespace std;

Card createCardFromString(string cs)
{
    // Cards of these sizes are impossible so we fix them.
    if (cs.length() > 3 || cs.length() < 2)
    {
        cout << "Error: Card is not of correct format. Defaulting to Ace of Spades." << endl;
        Card card;
        return card;
    }

    // Default number is 1 (Ace).
    int number = 1;
    // Default suit is Spades.
    Suit suit = Spades;

    // Conveniently grabbing last char from card string since it should be the suit under normal conditions.
    char suitChar = cs.at(cs.length() - 1);

    // Determine suit from suit char.
    switch(suitChar)
    {
        case 'S':
            suit = Spades;
            break;
        case 'H':
            suit = Hearts;
            break;
        case 'D':
            suit = Diamonds;
            break;
        case 'C':
            suit = Clubs;
            break;
        default:
            cout << "Error: Unrecognized suit \"" << suitChar << "\" while parsing card." << endl;
            break;
    }

    // Gets number from card string, assumes no numbers 3 characters long.
    string numberString = cs.length() > 2 ? cs.substr(0, 2) : cs.substr(0, 1);

    // Since 10 is the only card number that is 2 long, we can take this shortcut of only checking the length.
    if (cs.length() > 2)
        number = 10;
    else
    {
        if (isdigit(cs.at(0)))
        {
            // Shortcut conversion from char to int for numbers 0-9.
            number = cs.at(0) - '0';
        }
        else
        {
            switch(cs.at(0))
            {
                case 'A':
                    number = 1;
                    break;
                case 'J':
                    number = 11;
                    break;
                case 'Q':
                    number = 12;
                    break;
                case 'K':
                    number = 13;
                    break;
            }
        }
    }

    // Finally, we can create the card object and return it.
    Card card(number, suit);
    return card;
}

// Takes a hand and prints it to the console.
void printHand(vector<Card> hand)
{
    for (Card card : hand)
    {
        cout << card.getNumber() << card.getSuit() << " ";
    }
    cout << endl;
}

bool isSequential(vector<Card> hand)
{
    // We first sort the hand in ascending order.
    sort(hand.begin(), hand.end());

    // The trick here is to start a for loop at the lowest value of the hand. We can then check to see if the values of the hand
    // reflect the pattern of the the for loop counter (incrementing by 1 from hand start value to hand finish value).
    for (int i = 0; i < hand.size(); i++)
        if (hand[i].getNumber() != hand[0].getNumber() + i)
            return false;

    return true;
}

bool isSameSuit(vector<Card> hand)
{
    char suit = hand[0].getSuit();

    for (Card card : hand)
    {
        // We compare all other card suits to the suit of the first card in the hand. No need for sorting here.
        if (card.getSuit() != suit)
            return false;
    }

    return true;
}

// Handly helper function I made to check where a value is in a vector. Provides the index in return.
int contains(vector<int> list, int x)
{
    vector<int>::iterator iter;
    // One important note about this function is that it uses find, which stops at the first instance. This may not work for all use cases,
    // but it works for mine since I am managing a vector of unique values.
    iter = find(list.begin(), list.end(), x);

    // I like to return a -1 if value is not found, so I can check for it when I use the function.
    if (iter == list.end())
        return -1;

    // distance function allows us to count out how far in our iterator is, which is equal to the index.
    return distance(list.begin(), iter);
}

vector<int> countUniqueNumbers(vector<Card> hand)
{
    vector<int> visited; // List of unique visited values.
    vector<int> countVisited; // List of the number of encounters for each unique value from visited.

    int pairCount = 0, threeCount = 0, fourCount = 0;

    // The values of result provide the number of unique values, pairs count, threes count, and fours count, respectively.
    vector<int> result = {-1, -1, -1, -1};

    for (Card card : hand)
    {
        int idx = contains(visited, card.getNumber());

        // Case: Number not in visited set.
        if (idx == -1)
        {
            visited.push_back(card.getNumber());
            countVisited.push_back(1);
        }
        // Case: Number in visited set. Don't add, just increment.
        else
        {
            countVisited[idx]++;
        }
    }

    // Sum up statistics.
    for (int count : countVisited)
    {
        if (count == 2)
            pairCount++;
        
        if (count == 3)
            threeCount++;

        if (count == 4)
            fourCount++;
    }

    // The values of result provide the number of unique values, pairs count, threes count, and fours count, respectively.
    result[0] = visited.size();
    result[1] = pairCount;
    result[2] = threeCount;
    result[3] = fourCount;

    return result;
}

int getRankFromHand(vector<Card> hand, bool debug)
{
    if (debug)
    {
        cout << "Hand: ";
        printHand(hand);
    }

    // Here we utilize our helper functions, calling once and storing to save on function calls.
    bool sequential = isSequential(hand), sameSuit = isSameSuit(hand);
    vector<int> counts = countUniqueNumbers(hand);

    // We begin checking for hand criteria starting from best possible hand to worst possible hand.
    if (sequential && sameSuit)
    {
        // Case: Straight flush.
        if (debug)
            cout << "Straight flush." << endl;
        return 2;
    }

    if (counts[3] >= 1)
    {
        // Case: Four of a kind.
        if (debug)
            cout << "Four of a kind." << endl;
        return 3;
    }

    if (counts[1] >= 1 && counts[2] >= 1)
    {
        // Case: Full house.
        if (debug)
            cout << "Full house." << endl;
        return 4;
    }

    if (sameSuit)
    {
        // Case: Flush.
        if (debug)
            cout << "Flush." << endl;
        return 5;
    }

    if (sequential)
    {
        // Case: Straight.
        if (debug)
            cout << "Straight." << endl;
        return 6;
    }

    if (counts[2] >= 1)
    {
        // Case: Three of a kind.
        if (debug)
            cout << "Three of a kind." << endl;
        return 7;
    }

    if (counts[1] >= 2)
    {
        // Case: Two pair.
        if (debug)
            cout << "Two pair." << endl;
        return 8;
    }

    if (counts[1] == 1)
    {
        // Case One pair.
        if (debug)
            cout << "One pair." << endl;
        return 9;
    }

    sort(hand.begin(), hand.end());

    if (debug)
        cout << "High card." << endl;
    return 100 - hand[hand.size() - 1].getNumber();
}

void printWinner(vector<vector<int>> scores, bool ties)
{
    sort(scores.begin(), scores.end(), [](vector<int> a, vector<int> b) {
        return a[1] < b[1];
    });

    cout << "\nResults:" << endl;

    for (int i = 0; i < scores.size(); i++)
    {
        // This massive nested switch case is for adding ordinal indicators to the places.
        cout << i + 1;
        switch (i + 1 % 100)
        {
            case 1:
                cout << "st";
                break;
            case 2:
                cout << "nd";
                break;
            case 3:
                cout << "rd";
                break;
            case 11:
            case 12:
            case 13:
                cout << "th";
                break;
            default:
                switch (i + 1 % 10)
                {
                    case 1:
                        cout << "st";
                        break;
                    case 2:
                        cout << "nd";
                        break;
                    case 3:
                        cout << "rd";
                        break;
                    default:
                        cout << "th";
                }
                break;
        }
        cout << " place: Player " << scores[i][0] + 1 << "!";

        if (ties)
        {
            bool isTied = false;

            for (int j = 0; j < scores.size(); j++)
            {
                if (scores[i][1] == scores[j][1] && scores[i][0] != scores[j][0])
                {
                    if (!isTied)
                        cout << " Tied with:";
                    isTied = true;

                    cout << "  " << scores[j][0] + 1;
                }
            }
        }

        cout << endl;
    }
}