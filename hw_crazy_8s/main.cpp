#include<iostream>
#include<fstream>
#include<string>
#include "Card.h"
#include "Player.h"
#include "Game.h"
using std::string, std::cout, std::cin;

bool loadDeck(Game& g){
    string filename;
    std::cout << "Choose a file to load the deck from:" << std::endl;
    std::cin >> filename;
    try {
        g.loadDeckFromFile(filename);
    }
    catch (std::runtime_error const&) {
        std::cout << "The file was invalid. Aborting." << std::endl;
        return false;
    }
    return true;
}

int getPlayerCount(){
    std::cout << "Enter number of players:" << std::endl;
    int numPlayers;
    while (true) {
        numPlayers = -1;
        if(!(std::cin >> numPlayers) || numPlayers <= 0){
            std::cout << "Please enter a positive number" << "\n";
            if(std::cin.fail()){
                std::cin.clear();
                string garbage;
                std::cin >> garbage;
            }
            continue;
        }
        break;
        /*
        if ((!(std::cin >> numPlayers)) || numPlayers <= 0) {
            std::cout << "Please enter a positive number" << "\n";
            if (std::cin.fail()) {
                //clear fail
                std::cin.clear();
                cin.ignore(10000, '\n');
                string garbage;
                std::cin >> garbage;
                
            }
        }
        else {
            //break out of the loop once we've read a valid number
            break;
        }
        */
    }
    return numPlayers;
}

void setupPlayers(Game& g, int numPlayers){
    // TODO: Determine whether each player is a human or an AI
    // and add them to the game
    for (int i = 0; i < numPlayers; ++i) {
        string input;
        bool isValid = false;
        cout << "Is player " << i << " an AI? (y/n) " << "\n";
        while (!isValid) {
            cin >> input;
            if (input == "y" || input == "Y") {
                g.addPlayer(true); // add ai player
                isValid = true;
            } 
            else if (input == "n" || input == "N") {
                g.addPlayer(false); // add human player
                isValid = true;
            } 
            else {
                cout << "Please enter y or n" << "\n";
                //cout << "Is player " << i << " an AI? (y/n) " << "\n";
            }
        }
    }
}

void setupGame(Game& g) {
    // TODO: Determine how many cards to deal, deal the cards, and
    /*int numCards = 0;
    while (numCards <= 0) {
        cout << "How many cards should each player start with? ";
        cin >> numCards;

        if (numCards <= 0) {
            cout << "Please enter a positive number.\n";
        }
    }
    g.deal(numCards);*/
    //Card* top = g.drawCard()
    cout << "How many cards should each player start with?" << "\n"; 
    int numCards; 
    //bool game = true;
    while (true) { 
        if((!(cin >> numCards)) || numCards <= 0) {
            if (cin.fail()) {
                cin.clear();
                //if (cin.fail()) {
                string bad; 
                cin >> bad; 
                //}
                cout << "Please enter a positive number" << "\n"; 
            } 
        }
        else {
            //game = false;
            break;
        } 
    }
    Card* discard = g.deal(numCards); 
    cout << "The initial discard is " << discard->getRank() << " " << discard->getSuit() << "\n"; 
}


int main () {
    Game g;
    if(!loadDeck(g)){
        return 1;
    }
    int numPlayers = getPlayerCount();
    setupPlayers(g,numPlayers);
    setupGame(g);
    int winner = g.runGame();
    if(winner != -1) {
        std::cout << "Player " << winner << " wins!" << std::endl;
    }
    else {
        std::cout << "The game is a draw!" << std::endl;
    }
    std::cout << "The most played suit was " << g.mostPlayedSuit() << std::endl;
    return 0;
}