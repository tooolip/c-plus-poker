#include <string>
#include <vector>
using namespace std;

class Card;
Card createCardFromString(string cs);
int getRankFromHand(vector<Card> hand, bool debug);
void printWinner(vector<vector<int>> scores, bool ties);