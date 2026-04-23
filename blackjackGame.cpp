#include "blackjackGame.h"
#include "player.h"
#include "utils.h"
#include <iostream>
using namespace std;



//constructor initializes game with number of players and their names
BlackjackGame::BlackjackGame(int numPlayers, vector<string> playerNames) {
    this->numPlayers = numPlayers;
    this->playerNames = playerNames;
}

//dealer's turn logic: hits until reaching 17 or higher, with proper ace handling
void BlackjackGame::dealersTurn() {
    int value = 0;
    int aces = 0;

    for (auto& c : dealersdeck) {
        int v = getCardValue(c);
        value += v;
        if (c == "A") aces++;
    }

    // Dealer hits until reaching 17 or higher. 
    // Properly handle aces as 1 or 11 by counting them and adjusting value if it goes over 21.
    while (value < 17) {
        string newCard = retrievecards(1)[0];
        dealersdeck.push_back(newCard);

        int v = getCardValue(newCard);
        value += v;
        if (newCard == "A") aces++;

        while (value > 21 && aces > 0) {
            value -= 10;
            aces--;
        }

        cout << "Dealer hits: " << newCard << endl;
    }

    dealerValue = value;

    cout << "Dealer's final hand: ";
    for (auto& c : dealersdeck) cout << c << " ";
    cout << " = " << dealerValue << endl;
}


//players' turn logic: allows each player to choose actions until they stand, bust, double, or split
void BlackjackGame::PlayersTurn() {
    cout << "Players' turn...\n" << endl;

    for (int i = 0; i < numPlayers; i++) {
        cout << "\nPlayer " << playerNames.at(i) << ", it's your turn!" << endl;

        string action;
        bool done = false;

        while (!done) {
            cout << "\nChoose action (hit / stand / double / split): ";
            cin >> action;

            if (action == "hit") {
                // Player hits and receives a new card, then we check if they busted
                players[i].callingHit();
                int val = players[i].getHandValue();

                // If player busts, we set their result and end their turn immediately
                if (val > 21) {
                    cout << "You busted with " << val << endl;
                    players[i].setResult(val);
                    done = true;
                }
            }
            else if (action == "stand") {
                // Player stands, we set their result and end their turn
                int val = players[i].getHandValue();
                players[i].setResult(val);
                cout << "You stand with " << val << endl;
                done = true;
            }
            
            else if (action == "double") {
                int currentBet = players[i].getBet();
                int newBet = currentBet * 2;

                if (newBet <= players[i].getBankroll()) {
                players[i].setBet(newBet);

                players[i].callingHit();
                int val = players[i].getHandValue();
                players[i].setResult(val);

                cout << "You doubled down! New bet: " << newBet << endl;
                cout << "Final value: " << val << endl;

                done = true;
                } 
                else {
                   cout << "Not enough balance to double down." << endl;
                }
            }
            else if (action == "split") {
                if (players[i].canSplit()) {

                players[i].doSplit();

                vector<int> splitResults = players[i].usingSplit();

                players[i].setSplitResult(splitResults);

                done = true;

            } else {
                cout << "You cannot split this hand." << endl;
            }
        }
            else {
                cout << "Invalid action." << endl;
            }
        }
    }
}

// Logic to determine the outcome of a player's hand against the dealer's hand, accounting for busts and ties, added output of bet winnings
void BlackjackGame::ElevationLogic(Player& player, int playerValue, int dealerValue) {
    int bet = player.getBet();

    if (playerValue > 21) {
        cout << "You busted! Dealer wins." << endl;
        player.updateBankroll(-bet);
    }
    else if (dealerValue > 21) {
        cout << "Dealer busted! You win." << endl;
        player.updateBankroll(bet);
    }
    else if (playerValue > dealerValue) {
        cout << "You win with " << playerValue << " against dealer's " << dealerValue << "!" << endl;
        player.updateBankroll(bet);
    }
    else if (playerValue < dealerValue) {
        cout << "Dealer wins with " << dealerValue << " against your " << playerValue << "." << endl;
        player.updateBankroll(-bet);
    }
    else {
        cout << "It's a tie with both at " << playerValue << "." << endl;
        // no change
    }

    cout << "New balance: " << player.getBankroll() << endl;
}

// Main game logic: initializes players, deals initial cards, manages turns, and evaluates results at the end
//game flow: 1) initialize players and deal initial cards, 2) players take turns, 3) dealer takes turn, 4) evaluate results
void BlackjackGame::startGame() {
    cout << "\n\nStarting the game..." << endl;

    players.clear();
    players.reserve(numPlayers);
//modified loop logic to include bankroll and player creation
for (int i = 0; i < numPlayers; i++) {
    int bet = 0;

    //create player (so bankroll exists)
    players.emplace_back(playerNames.at(i), 0);

    //validate bet using bankroll
    while (true) {
        cout << "\nPlayer " << playerNames.at(i)
             << ", enter bet (available: "
             << players[i].getBankroll() << "): ";
        cin >> bet;

        if (bet > 0 && bet <= players[i].getBankroll()) break;

        cout << "Invalid bet. Try again.\n";
    }

    //store bet
    players[i].setBet(bet);

    //deal cards
    vector<string> cards = retrievecards(2);
    players[i].addToHand(cards);
    players[i].displayHand();
}

    

    cout << "\n\nDealer's turn..." << endl;
    dealersdeck = retrievecards(2);
    cout << "Dealer shows: " << dealersdeck[0] << " [Hidden]" << endl;

    cout << "\n\nNow it's time for the players to take their turns!" << endl;
    PlayersTurn();

    cout << "\n\nNow it's time for the dealer's turn!" << endl;
    dealersTurn();

    cout << "\n\nLet's see who wins...\n" << endl;
    for (int i = 0; i < numPlayers; i++) {
        cout << "Evaluating Player " << playerNames.at(i) << "..." << endl;
        // If the player has split, we need to evaluate both hands separately
        if (players[i].hasSplitHand()) {
            vector<int> splitResults = players[i].getSplitResult();
            for (size_t j = 0; j < splitResults.size(); j++) {
                cout << "  Split hand " << (j + 1) << ": ";
                int playerValue = splitResults[j];
                ElevationLogic(players[i], playerValue, dealerValue);
            }
        } else {
            int playerValue = players[i].getResult();
            ElevationLogic(players[i], playerValue, dealerValue);
        }
    }
}
