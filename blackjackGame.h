#ifndef BLACKJACKGAME_H
#define BLACKJACKGAME_H

#include <iostream>
#include <vector>
#include "player.h"
using namespace std;

class BlackjackGame {
private:
    int numPlayers;
    vector<string> playerNames;

    //decker for the dealer and its value
    vector<string> dealersdeck;
    int dealerValue = 0;
    // List of players in the game
    vector<Player> players;

    void ElevationLogic(Player& player, int playerValue, int dealerValue);

public:
    BlackjackGame(int numPlayers, vector<string> playerNames);
    //game flow
    void startGame();
    void PlayersTurn();
    void dealersTurn();
};

#endif
