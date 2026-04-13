#include "utils.h"
#include <cstdlib>
#include <ctime>

static const vector<string> deck = {
    "A","2","3","4","5","6","7","8","9","10","J","Q","K"
};

// Retrieves a specified number of cards from the deck and returns them as a vector of strings
vector<string> retrievecards(int n) {
    static bool seeded = false;
    if (!seeded) {
        srand(time(nullptr)); // Seed the random number generator once
        seeded = true;
    }

    vector<string> cards;
    cards.reserve(n);

    for (int i = 0; i < n; i++) {
        int index = rand() % deck.size();
        cards.push_back(deck[index]);
    }

    return cards;
}
// Converts card string to blackjack value
int getCardValue(const string& card) {
    if (card == "A") return 11;
    if (card == "K" || card == "Q" || card == "J") return 10;
    return stoi(card); 
}
