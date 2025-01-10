#include<iostream>
#include<sstream>
#include "Player.h"
using std::vector, std::string, std::size_t, std::cout, std::cin;

Player::Player(bool isAI) : isAI(isAI), hand() /*isAI is utilized in playCard*/ {

}

void Player::addToHand(Card* c){
    // TODO: Add the card c to the player's hand
    hand.push_back(c);
}

size_t Player::getHandSize(){
    // TODO: Implement getter
    return hand.size();
}

std::string Player::getHandString(){
    // TODO: Implement getter
    string handString;
    string add;
    for (size_t i = 0; i < hand.size(); ++i) {
        add = hand[i]->getRank() + " " + hand[i]->getSuit();
        handString = handString + add;
        if (i != hand.size() - 1) { // might need to do ahnd.size() - 1 
            handString += ", ";
        }
    }
    return handString;
}

Card* Player::playCard(vector<string> const& suits, string& currentRank, string& currentSuit){
    // TODO: Choose a card to play and return the chosen card
    if (isAI) {
        // ai: play first valid card or return nullptr if no valid cards exitr
        for (size_t i = 0; i < hand.size(); ++i) {
            if (hand[i]->canBePlayed(currentRank, currentSuit)) { //  is card playable
                Card* card = hand[i];
                hand.erase(hand.begin() + i); // remove from hand
                card->play();

                // special 8's case
                if (card->getRank() == "8") {
                    currentRank = "8";
                    currentSuit = card->getSuit(); // choose a suit
                } 
                else {
                    currentRank = card->getRank();
                    currentSuit = card->getSuit();
                }
                return card;
            }
        }
        return nullptr; // no valid cards so AI draws
    } 
    else {
        // human player
        cout << "Your hand contains: " << getHandString() << "\n";
        cout << "The next card played must be a " << currentRank << " or " << currentSuit << "\n";
        cout << "What would you like to play? (enter \"draw card\" to draw a card)" << "\n";
        string chosenRank, chosenSuit;
        while (true) {
            cin >> chosenRank;
            cin >> chosenSuit;
            if (chosenRank == "draw" || chosenSuit == "card") { // || chosenRank == "draw card") {
                return nullptr; // draw card
            }
            Card* chosenCard = nullptr;
            bool cardInHand = false;
            bool cardExists = false;
            // check if card in hand and playable
            for (size_t i = 0; i < hand.size(); ++i) {
                if (hand[i]->getRank() == chosenRank && hand[i]->getSuit() == chosenSuit) {
                    chosenCard = hand[i];
                    if (chosenCard->canBePlayed(currentRank, currentSuit)) { // playable or not
                        cardInHand = true;
                        hand.erase(hand.begin() + i); // remove card
                        chosenCard->play();
                        currentRank = chosenCard->getRank();
                        // currentSuit = chosenCard->getSuit();
                        // 8s means player can change suit
                        if (chosenCard->getRank() == "8") {
                            cout << "What suit would you like to declare?" << "\n";
                            string changeS;
                            while (true) {
                                cin >> changeS;
                                // valid suit?
                                bool isValidSuit = false;
                                for (unsigned int i = 0; i < suits.size(); i++) {
                                    if (changeS == suits[i]) {
                                        isValidSuit = true;
                                        break;
                                    }
                                }
                                if (isValidSuit) {
                                    currentSuit = changeS;
                                    break;
                                } 
                                else {
                                    cout << "That's not a suit in this deck. Try again" << ".\n";
                                }
                            }
                        }
                        else {
                            currentSuit = chosenCard->getSuit();
                        }
                        return chosenCard; // return card
                    } 
                    else {
                        cout << "You can't play that card. Try again" << ".\n";
                        break;
                        cardExists = true;
                        chosenCard = nullptr; // reset if unplayable card & give player secomd chance
                    }
                    break;
                }
                //break;
            }
            if (cardExists==false) {
                if (!chosenCard && cardInHand == false) {
                    cout << "That's not a card you have. Try again" << ".\n";
                }
            }
        }
    }
    return nullptr;
} 
