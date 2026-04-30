#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "player.h"
using namespace std;

class Scoreboard {
private:
    string filename;

public:
    Scoreboard(string file);

    //file handling logic
    void savePlayers(const vector<Player>& players);
    void loadPlayers(vector<Player>& players);

    //display saved stats
    void displayScoreboard() const;
    //reset certain players
    void resetPlayers(const vector<Player>& players);
};

#endif