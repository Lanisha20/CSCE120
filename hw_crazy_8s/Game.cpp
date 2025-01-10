#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include "Game.h"
using std::string, std::vector, std::ifstream, std::runtime_error, std::cout;

Game::Game(): players({}), suits({}), ranks({}), 
    deck({}), drawPile({}), discardPile({}) {}


void Game::loadDeckFromFile(string filename){
    // TODO: initialize suits, ranks, deck, and drawPile from the given file
    ifstream file(filename);
    if (!(file.is_open())) {
        throw runtime_error("Couldn't open file: " + filename);
    }
    string rank, suit;
    //std::vector<std::string> validR = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"}; //do i need to go back and add lowercse values
    //std::vector<std::string> validS = {"Hearts", "Clubs", "Diamonds", "Spades"}; //, "hearts", "clubs", "diamonds", "spades"};
    //std::vector<std::string> validR;
    //std::vector<std::string> validS;

    string line;
    //std::getline(file, line);
    if (!std::getline(file, line)) {
        throw std::runtime_error("File is empty or missing suit data.");
    }
    //if (std::getline(file, line)) {
    std::istringstream ss(line);
    //cout << line;
    while (ss >> suit) {
        suits.push_back(suit);
        //cout << suit;
    }
    //}
    //if (std::getline(file, line)) {
    string line2;
    if (!std::getline(file, line2)) {
        throw std::runtime_error("File is missing rank data.");
    }
    //std::getline(file, line2);
    std::istringstream sr(line2);
    while (sr >> rank) {
        ranks.push_back(rank); 
    }
    //}

    //file >> validR;
    //file >> validS;
    string line3;
    while (std::getline(file,line3)) {
        std::istringstream st(line3);
        string cardRank;
        string cardSuit;

        if (!(st >> cardRank)) {
            std::runtime_error("File missing suit data");
        }
        if (!(st >> cardSuit)) {
            std::runtime_error("File missing rank data");
        }
        string garb;
        if(st >> garb || !(garb.empty())){
            throw std::runtime_error("Extra card data");
        }
        
        //std::cout << "|" << cardSuit << "| |" << cardRank << "| |" << garb.size() << "|" << std::endl;
        bool isValR = false;
        for (size_t i = 0; i < ranks.size(); ++i) {
            if (cardRank == ranks[i]) {
                isValR = true;
                if (cardRank.empty()) {
                    throw std::runtime_error("Invalid card in file: " + cardRank + " " + cardSuit);
                }
                break;
            }
        }
        bool isValS = false;
        for (size_t i = 0; i < suits.size(); ++i) {
            if (cardSuit == suits[i]) {
                isValS = true;
                if (cardSuit.empty()) {
                    throw std::runtime_error("Invalid card in file: " + cardRank + " " + cardSuit);
                }
                break;
            }
        }
        // suit invalid or rank empty
        if (cardRank.empty() || cardSuit.empty() || !isValR || !isValS) {
            throw std::runtime_error("Invalid card in file: " + cardRank + " " + cardSuit);
        }
        try {
            Card* card = new Card(cardRank, cardSuit);
            deck.push_back(card);
            drawPile.insert(drawPile.begin(), card); //reverse
        } 
        catch (const std::invalid_argument&) {
            throw std::runtime_error("Invalid card data");
        }
    }

    if (file.bad()) {
        throw std::runtime_error("Error reading " + filename);
    }

    file.close(); // closing file 
}

void Game::addPlayer(bool isAI) {
    // TODO: add a new player to the game
    Player* newPl = new Player(isAI);
    players.push_back(newPl);
}

void Game::drawCard(Player* p){
    // TODO: Move the top card of the draw pile to Player p's hand
    // If the draw pile is empty, flip the discard pile to create a new one
    if (drawPile.empty()) {
        
        if (discardPile.size() <= 1) {
            throw std::runtime_error("No cards left to draw");
        }
        std::cout << "Draw pile, empty, flipping the discard pile.\n";
        Card* reservedCard = discardPile.back();
        discardPile.pop_back();
        // p->addToHand(card);
            /*Card* card = discardPile.front();
            discardPile.erase(discardPile.begin());
            drawPile.push_back(card);*/
        //throw std::runtime_error("No cards left to draw");
        while (!(discardPile.empty())) {
            drawPile.push_back(discardPile.back());
            discardPile.pop_back();
        }
        discardPile.push_back(reservedCard);
    }
    // draw top card
    Card* card = drawPile.back();
    drawPile.pop_back();
    p->addToHand(card);
}

//deals numCards cards to each player
Card* Game::deal(int numCards){
    // TODO: Flip the top card of the draw pile to be the initial discard
    // then deal numCards many cards to each player
    if (drawPile.empty()) {
        throw std::runtime_error("Draw pile is empty");
    }
    Card* discard = drawPile.back();
    drawPile.pop_back();
    discardPile.push_back(discard);
    for (int i = 0; i < numCards; ++i) {
        for (size_t j = 0; j < players.size(); ++j) {
            drawCard(players[j]);  // deal one card to each
        }
    }
    return discard;
}

string Game::mostPlayedSuit(){
    // TODO: Return the suit which has been played the most times
    // if there is a tie, choose any of the tied suits
    //vector<string> suits = {"Hearts", "Clubs", "Diamonds", "Spades"};
    // array that will be incrememnted every time a suit is played
    vector<int> count(suits.size(), 0);
    for (Card* card : deck) {
        string suit = card->getSuit();
        int timesPlayed = card->getTimesPlayed();
        for (unsigned int j = 0; j < suits.size(); j++) {
            if (suit == suits[j]) { 
                count[j] += timesPlayed;
            }
        }
    }
    int mostPlayed = 0;
    int suitIndex = 0;
    for (unsigned int i = 0; i < count.size(); i++) {
        if (count[i] > mostPlayed) {
            mostPlayed = count[i];
            suitIndex = i;
        }
    }
    return suits[suitIndex];
}

int Game::runGame() {
    // TODO: Run the game and return the number of the winning player
    //bool continueGame = true;
    int winner;
    Card* discardTop = discardPile.back();
    string currentRank = discardTop->getRank(); //inital discard card & initialize card and suit
    string currentSuit = discardTop->getSuit();
    //discardPile.push_back(deck.at(0));  // add to discrad pile
    int i = 0;
    while (true) {
        //for (size_t i = 0; i < (i+1)%players.size(); ++i) {
            std::cout << "Player " << i << "'s turn!" << "\n";
            Card* playedCard = players.at(i)->playCard(suits, currentRank, currentSuit);
            if (playedCard == nullptr) {  // player must draw a card since no playable card exists in their hand
                try {
                    drawCard(players.at(i));  // draws card if pile isnt empty
                    cout << "Player " << i << " draws a card.\n";
                }
                catch (std::runtime_error const&) { 
                    cout << "Player " << i << " cannot draw a card." << "\n";
                    //continueGame = false;
                    return -1;  // draw if deck empty
                }
            } 
            else { // card plays 
                // crazy 8s special case
                cout << "Player " << i << " plays " << playedCard->getRank() << " " << playedCard->getSuit();
                if (currentRank == "8") {
                    cout << " and changes the suit to " << currentSuit << ".\n";
                } 
                else {
                    cout << ".\n";
                }
                if (discardPile.empty()) {
                    throw std::runtime_error("Discard pile is empty");
                }
                discardPile.push_back(playedCard); // discard card that was played
            }
            if (players.at(i)->getHandSize() == 0) { // has anyone won?
                //continueGame = false;
                winner = i;  // if yes return index of winning player
                return winner;
            }
        //}
        i = (i+1) % players.size();
        //}
    //return -1;
    // return winner;
    //return 0;
    }
}

//Destructor--Deallocates all the dynamic memory we allocated
Game::~Game(){
    for (unsigned int i = 0; i < deck.size(); i++){
        delete deck.at(i);
    }
    for (unsigned int i = 0; i < players.size(); i++) {
        delete players.at(i);
    }
}