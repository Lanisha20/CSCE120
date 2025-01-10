#include<cctype>
#include<stdexcept>
#include "Card.h"
using std::string;

/*class Card {
    public:
        Card(string rank, string suit);
        // getters
        string getRank();
        string getSuit();
        int getTimesPlayed();
        // methods
        bool canBePlayed(string currentRank, string currentSuit);
        void play ();

    private:
        string rank;
        string suit;
}; */ // already declared in test files?

Card::Card(string rank, string suit) : rank(rank), suit(suit), timesPlayed(0) {
    // TODO: implement constructor checks

    if (rank.empty() || suit.empty()) {
        throw std::invalid_argument("Rank or suit cannot be empty.");
    }

    // rank contains only alphanumeric characters
    for (size_t i = 0; i < rank.length(); i++) {
        if (!((rank[i] >= 'A' && rank[i] <= 'Z') || (rank[i] >= 'a' && rank[i] <= 'z') || (rank[i] >= '0' && rank[i] <= '9'))) {
            throw std::invalid_argument("Rank must contain only letters and numbers.");
        }
    }

    // suit contains only alphanumeric characters
    for (size_t j = 0; j < suit.length(); j++) {
        if (!((suit[j] >= 'A' && suit[j] <= 'Z') || (suit[j] >= 'a' && suit[j] <= 'z') || (suit[j] >= '0' && suit[j] <= '9'))) {
            throw std::invalid_argument("Rank must contain only letters and numbers.");
        }
    }

    this->rank = rank;
    this->suit = suit;
}

string Card::getRank(){
    // TODO: implement getter
    return rank;
}

string Card::getSuit(){
    // TODO: implement getter
    return suit;
}

int Card::getTimesPlayed(){
    // TODO: implement getter
    return timesPlayed;
}

bool Card::canBePlayed(string currentRank, string currentSuit){
    // TODO: return whether or not the card can legally be played 
    if (rank == "8") { // 8s are wild and can always be played
        return true;
    }
    else {
        return (rank == currentRank || suit == currentSuit);
    }
}

void Card::play(){
    timesPlayed++;
}

// full points achieved for this file