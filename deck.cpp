#include "deck.h"
#include <algorithm>
#include <random>

//constructor builds full 52 card deck
Deck::Deck() {
    vector<string> ranks = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

    for (int i = 0; i < 4; i++) { //4 suits
        for (const auto& r : ranks) {
            cards.push_back(r);
        }
    }

    shuffleDeck();
}

//shuffle the deck
//shuffle the deck
void Deck::shuffleDeck() {
    random_device rd;
    mt19937 g(rd());

    shuffle(cards.begin(), cards.end(), g);
}

//draw n cards and remove them from deck
vector<string> Deck::drawCards(int n) {
    vector<string> drawn;

    for (int i = 0; i < n && !cards.empty(); i++) {
        drawn.push_back(cards.back());
        cards.pop_back(); //REMOVES card from deck
    }

    return drawn;
}

//return number of remaining cards
int Deck::size() const {
    return cards.size();
}

//return remaining cards in deck
vector<string> Deck::getRemainingCards() const {
    return cards;
}