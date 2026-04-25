#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Returns N random cards as strings 
vector<string> retrievecards(int n);

// Converts card string to blackjack value
int getCardValue(const string& card);

//probability helper
string getSuggestion(int value);

#endif
