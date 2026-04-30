#ifndef STATS_H
#define STATS_H

#include <iostream>
using namespace std;

class Stats {
private:
    int wins;
    int losses;
    int pushes;
    int blackjacks;
    int busts;
    int totalMoney;

public:
    Stats();

    //set stat values
    void setStats(int w, int l, int p, int bj, int b, int money);

    //record game results
    void recordWin();
    void recordLoss();
    void recordPush();
    void recordBlackjack();
    void recordBust();

    //money tracking
    void setTotalMoney(int money);
    int getTotalMoney() const;

    //display stats
    void displayStats() const;

    //get stat values
    int getWins() const;
    int getLosses() const;
    int getPushes() const;
    int getBlackjacks() const;
    int getBusts() const;       
};

#endif