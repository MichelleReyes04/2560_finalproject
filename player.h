#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "stats.h"
using namespace std;

class Deck;

class Player {
private:
    string name;
    vector<string> hand;
    int bet;
    int bankroll;
    Stats stats;

    // Split hands
    vector<string> hand1;
    vector<string> hand2;
    bool hasSplit = false;

    
    //results for final evaluation against dealer
    int result = 0;
    vector<int> splitResults;

    //Add card values in a hand
    int addAllCardValues(const vector<string>& h) const;

public:
    Player(string playerName, int bet, int startingBalance = 100);

    // Basic hand
    void addToHand(const vector<string>& cards);
    void displayHand() const;
    int getHandValue() const;
    vector<string> getHand() const;
    int getBankroll() const;
    void updateBankroll(int amount);
    int getBet() const;
    void setBet(int b);

   
    string getName() const;

    // Actions
    void callingHit(Deck& deck);          // hit main hand
    bool canSplit() const;      // Split check
    void doSplit();             // perform split
    vector<int> usingSplit();   // play both split hands
    bool hasSplitHand() const { return hasSplit; }  // Check if player has split hand

    // Results
    void setResult(int res);
    int getResult() const;

    void setSplitResult(const vector<int>& res);
    vector<int> getSplitResult() const;

    // Stats
    Stats& getStats();
    const Stats& getStats() const;  
    void displayStats() const;

    
    void setBankroll(int amount);
    void clearHand();

    
};

#endif
