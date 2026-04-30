#ifndef DECK_H
#define DECK_H

#include <vector>
#include <string>

using namespace std;

class Deck {
private:
    vector<string> cards;

public:
    Deck();

    //shuffle the deck
    void shuffleDeck();

    //draw n cards and remove them from deck
    vector<string> drawCards(int n);

    //check remaining cards
    int size() const;

    //return remaining cards in deck
    vector<string> getRemainingCards() const;
};

#endif