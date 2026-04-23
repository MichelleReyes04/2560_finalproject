#include "player.h"
#include "utils.h"
#include <iostream>
using namespace std;

//constructor initializes player with name and bet amount, and starting balance
Player::Player(string playerName, int bet, int startingBalance) {
    this->name = playerName;
    this->bet = bet;
    this->bankroll = startingBalance;
}

// Adds new cards to the player's hand
void Player::addToHand(const vector<string>& cards) {
    for (const auto& c : cards) {
        hand.push_back(c);
    }
}

// Returns the current hand value
vector<string> Player::getHand() const {
    return hand;
}

// Displays the player's hand and its current value
void Player::displayHand() const {
    cout << name << "'s hand: ";
    for (const auto& c : hand) {
        cout << c << " ";
    }
    cout << "(value: " << getHandValue() << ")" << endl;
}

// Helper function to calculate the total value of a hand, properly handling aces
int Player::addAllCardValues(const vector<string>& h) const{
    int value = 0;
    int aces = 0;

    for (const auto& c : h) {
        int v = getCardValue(c);
        value += v;
        if (c[0] == 'A') aces++;
    }

    while (value > 21 && aces > 0) {
        value -= 10;
        aces--;
    }

    return value;
}

// Returns the total value of the player's hand
int Player::getHandValue() const {
    return addAllCardValues(hand);
};

// Returns the player's name
string Player::getName() const {
    return name;
}

// Logic for player choosing to hit: adds a card to their hand and displays the new hand
void Player::callingHit() {
    vector<string> card = retrievecards(1);
    hand.push_back(card[0]);
    cout << name << " hits and receives: " << card[0] << endl;
    displayHand();
}

// Checks if the player's hand can be split 
bool Player::canSplit() const {
    if (hand.size() != 2) return false;
    return hand[0][0] == hand[1][0];
}

// Logic for splitting the player's hand into two separate hands and dealing one new card to each
void Player::doSplit() {
    if (!canSplit()) return;

    hasSplit = true;
    hand1.clear();
    hand2.clear();

    hand1.push_back(hand[0]);
    hand2.push_back(hand[1]);
    hand.clear();

    vector<string> c1 = retrievecards(1);
    vector<string> c2 = retrievecards(1);
    hand1.push_back(c1[0]);
    hand2.push_back(c2[0]);

    cout << name << " splits into two hands:" << endl;

    cout << "Hand 1: ";
    for (auto& c : hand1) cout << c << " ";
    cout << "(value: " << addAllCardValues(hand1) << ")" << endl;

    cout << "Hand 2: ";
    for (auto& c : hand2) cout << c << " ";
    cout << "(value: " << addAllCardValues(hand2) << ")" << endl;
}



// Logic for playing out both split hands: allows the player to hit or stand on each hand separately and returns the final values of both hands
vector<int> Player::usingSplit() {
    vector<int> results;

    auto playHand = [&](vector<string>& h, const string& label) {
        bool done = false;
        while (!done) {
            cout << "Playing " << label << " for " << name << ". Current hand: ";
            for (auto& c : h) cout << c << " ";
            int val = addAllCardValues(h);
            cout << "(value: " << val << ")" << endl;

            if (val > 21) {
                cout << label << " busted!" << endl;
                return val;
            }

            string action;
            cout << "Choose action for " << label << " (hit / stand): ";
            cin >> action;

            if (action == "hit") {
                vector<string> card = retrievecards(1);
                h.push_back(card[0]);
                cout << name << " hits and receives: " << card[0] << endl;
            }
            else if (action == "stand") {
                cout << name << " stands with " << val << endl;
                return val;
            }
            else {
                cout << "Invalid action. Please choose 'hit' or 'stand'." << endl;
            }
        }
        return addAllCardValues(h);// should never reach here or could be 0 since all exists are covered
    };

    int v1 = playHand(hand1, "Hand 1");
    int v2 = playHand(hand2, "Hand 2");

    results.push_back(v1);
    results.push_back(v2);

    return results;
}

// Setters and getters for the player's result after their turn is over, used for final evaluation against the dealer's hand
void Player::setResult(int res) {
    result = res;
}

int Player::getResult() const {
    return result;
}

void Player::setSplitResult(const vector<int>& res) {
    splitResults = res;
}

vector<int> Player::getSplitResult() const {
    return splitResults;
}

//set the bet 
void Player::setBet(int b) {
    bet = b;
}

//functiom to output current bankroll balance
int Player::getBankroll() const{
    return bankroll;
}

//function to get bet amount
int Player::getBet() const{
    return bet;
}

//function to update bankroll amount after the round
void Player::updateBankroll(int amount){
    bankroll += amount;
}