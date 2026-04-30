#include "stats.h"
#include <iostream>
using namespace std;

//constructor initializes all stats to 0 and starting money to 100
Stats::Stats() {
    wins = 0;
    losses = 0;
    pushes = 0;
    blackjacks = 0;
    busts = 0;
    totalMoney = 100;
}

//set all stat values, used when loading from file
void Stats::setStats(int w, int l, int p, int bj, int b, int money) {
    wins = w;
    losses = l;
    pushes = p;
    blackjacks = bj;
    busts = b;
    totalMoney = money;
}

//record a win
void Stats::recordWin() {
    wins++;
}

//record a loss
void Stats::recordLoss() {
    losses++;
}

//record a push
void Stats::recordPush() {
    pushes++;
}

//record a blackjack
void Stats::recordBlackjack() {
    blackjacks++;
}

//record a bust
void Stats::recordBust() {
    busts++;
}

//set total money to match player's bankroll
void Stats::setTotalMoney(int money) {
    totalMoney = money;
}

//return total money
int Stats::getTotalMoney() const {
    return totalMoney;
}

//return wins
int Stats::getWins() const {
    return wins;
}

//return losses
int Stats::getLosses() const {
    return losses;
}

//return pushes
int Stats::getPushes() const {
    return pushes;
}

//return blackjacks
int Stats::getBlackjacks() const {
    return blackjacks;
}

//return busts
int Stats::getBusts() const {
    return busts;
}

//display all current stats
void Stats::displayStats() const {
    cout << "\n===== Player Stats =====" << endl;
    cout << "Wins: " << wins << endl;
    cout << "Losses: " << losses << endl;
    cout << "Pushes: " << pushes << endl;
    cout << "Blackjacks: " << blackjacks << endl;
    cout << "Busts: " << busts << endl;
    cout << "Total Money: " << totalMoney << endl;
    cout << "========================" << endl;
}

