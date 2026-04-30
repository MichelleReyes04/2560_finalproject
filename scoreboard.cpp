#include "scoreboard.h"
#include "stats.h"
#include "player.h"
#include <map>

//constructor sets the file name
Scoreboard::Scoreboard(string file) {
    filename = file;
}

//save all players to file
//save all players to file without deleting old players
void Scoreboard::savePlayers(const vector<Player>& players) {
    map<string, vector<int>> savedPlayers;

    ifstream inFile(filename);

    string savedName;
    int wins;
    int losses;
    int pushes;
    int blackjacks;
    int busts;
    int money;

    //load old scoreboard data first
    while (inFile >> savedName >> wins >> losses >> pushes >> blackjacks >> busts >> money) {
        savedPlayers[savedName] = {wins, losses, pushes, blackjacks, busts, money};
    }

    inFile.close();

    //update only current players
    for (const auto& player : players) {
        savedPlayers[player.getName()] = {
            player.getStats().getWins(),
            player.getStats().getLosses(),
            player.getStats().getPushes(),
            player.getStats().getBlackjacks(),
            player.getStats().getBusts(),
            player.getBankroll()
        };
    }

    ofstream outFile(filename);

    if (!outFile) {
        cout << "Could not open scoreboard file for saving." << endl;
        return;
    }

    //rewrite full scoreboard with old and updated players
    for (const auto& pair : savedPlayers) {
        outFile << pair.first << " "
                << pair.second[0] << " "
                << pair.second[1] << " "
                << pair.second[2] << " "
                << pair.second[3] << " "
                << pair.second[4] << " "
                << pair.second[5] << endl;
    }

    outFile.close();
}

//load saved player data from file
void Scoreboard::loadPlayers(vector<Player>& players) {
    ifstream inFile(filename);

    if (!inFile) {
        cout << "No saved scoreboard found. Starting fresh." << endl;
        return;
    }

    string savedName;
    int wins;
    int losses;
    int pushes;
    int blackjacks;
    int busts;
    int money;

    while (inFile >> savedName >> wins >> losses >> pushes >> blackjacks >> busts >> money) {
        for (auto& player : players) {
            if (player.getName() == savedName) {
                player.setBankroll(money);
                player.getStats().setStats(wins, losses, pushes, blackjacks, busts, money);
            }
        }
    }

    inFile.close();
}

//display all saved players from file
void Scoreboard::displayScoreboard() const {
    ifstream inFile(filename);

    if (!inFile) {
        cout << "\nNo scoreboard data found." << endl;
        return;
    }

    cout << "\n===== Full Scoreboard =====" << endl;

    string name;
    int wins, losses, pushes, blackjacks, busts, money;

    while (inFile >> name >> wins >> losses >> pushes >> blackjacks >> busts >> money) {
        cout << "\nPlayer: " << name << endl;
        cout << "Wins: " << wins << endl;
        cout << "Losses: " << losses << endl;
        cout << "Pushes: " << pushes << endl;
        cout << "Blackjacks: " << blackjacks << endl;
        cout << "Busts: " << busts << endl;
        cout << "Total Money: " << money << endl;
    }

    cout << "\n===========================" << endl;

    inFile.close();
}

//reset only current players in the scoreboard file
void Scoreboard::resetPlayers(const vector<Player>& players) {
    map<string, vector<int>> savedPlayers;

    ifstream inFile(filename);

    string savedName;
    int wins;
    int losses;
    int pushes;
    int blackjacks;
    int busts;
    int money;

    while (inFile >> savedName >> wins >> losses >> pushes >> blackjacks >> busts >> money) {
        savedPlayers[savedName] = {wins, losses, pushes, blackjacks, busts, money};
    }

    inFile.close();

    for (const auto& player : players) {
        savedPlayers[player.getName()] = {0, 0, 0, 0, 0, 100};
    }

    ofstream outFile(filename);

    if (!outFile) {
        cout << "Could not open scoreboard file for resetting." << endl;
        return;
    }

    for (const auto& pair : savedPlayers) {
        outFile << pair.first << " "
                << pair.second[0] << " "
                << pair.second[1] << " "
                << pair.second[2] << " "
                << pair.second[3] << " "
                << pair.second[4] << " "
                << pair.second[5] << endl;
    }

    outFile.close();
}