#ifndef BLACKJACKGAME_H
#define BLACKJACKGAME_H

#include <iostream>
#include <vector>
#include "player.h"
#include "deck.h"
using namespace std;

class BlackjackGame {
private:
    vector<Player>& players;
    Deck deck;

    //deck for the dealer and its value
    vector<string> dealersdeck;
    int dealerValue = 0;

    void ElevationLogic(Player& player, int playerValue, int dealerValue);

public:
    BlackjackGame(vector<Player>& players);

    //game flow
    void startGame();
    void PlayersTurn();
    void dealersTurn();
    
};

#endif