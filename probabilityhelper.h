#ifndef PROBABILITYHELPER_H
#define PROBABILITYHELPER_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class ProbabilityHelper {
public:
    //calculate chance of busting if player hits
    static double calculateBustChance(int handValue, const vector<string>& remainingCards);

    //suggest whether player should hit or stand
    static string getSuggestion(int handValue, const vector<string>& remainingCards);
};

#endif