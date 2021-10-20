enum Suit {Spades, Hearts, Diamonds, Clubs};

class Card
{
    public:
        Card()
        {
            _number = 1;
            _suit = Spades;
        }

        Card(int number, Suit suit)
        {
            _number = number;
            _suit = suit;
        }

        void setNumber(int number)
        {
            _number = number;
        }

        int getNumber()
        {
            return _number;
        }

        void setSuit(Suit suit)
        {
            _suit = suit;
        }

        Suit getSuitAsInt()
        {
            return _suit;
        }

        char getSuit()
        {
            switch (_suit)
            {
                case Spades:
                    return 'S';
                    break;
                case Hearts:
                    return 'H';
                    break;
                case Diamonds:
                    return 'D';
                    break;
                case Clubs:
                    return 'C';
                    break;
                default:
                    return 'N';
                    break;
            }
        }

        bool operator <(const Card & card) const
        {
            return _number < card._number;
        }
    private:
        int _number;
        Suit _suit;
};