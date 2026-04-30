#include "blackjackGame.h"
#include "player.h"
#include "utils.h"
#include "probabilityhelper.h"
#include <iostream>
using namespace std;



//constructor connects game to existing players
BlackjackGame::BlackjackGame(vector<Player>& players) : players(players) {
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
        string newCard = deck.drawCards(1)[0];
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

    for (int i = 0; i < players.size(); i++) {

        string action;
        bool done = false;

        while (!done) {
            cout << "\n==============================" << endl;
            cout << "Player " << players[i].getName() << ", it's your turn!" << endl;
            cout << "Current bet: " << players[i].getBet() << endl;
            cout << "Current balance: " << players[i].getBankroll() << endl;
            cout << "\nCurrent hand:" << endl;
            players[i].displayHand();
            cout << endl;
            cout << "Dealer showing: " << dealersdeck[0] << endl;
            int val = players[i].getHandValue();
            cout << endl;
            cout << "Suggestion: "
                << ProbabilityHelper::getSuggestion(val, deck.getRemainingCards())
                << endl;
            cout << "==============================" << endl;
            cout << endl;

            cout << "\nChoose action (hit / stand / double / split): ";
            cin >> action;

            if (action == "hit") {
                // Player hits and receives a new card, then we check if they busted
                players[i].callingHit(deck);
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

                players[i].callingHit(deck);
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
        player.getStats().recordBust();
        player.getStats().recordLoss();
    }
    else if (dealerValue > 21) {
        cout << "Dealer busted! You win." << endl;
        player.updateBankroll(bet);
        player.getStats().recordWin();
    }
    else if (playerValue > dealerValue) {
        cout << "You win with " << playerValue << " against dealer's " << dealerValue << "!" << endl;
        player.updateBankroll(bet);
        player.getStats().recordWin();
    }
    else if (playerValue < dealerValue) {
        cout << "Dealer wins with " << dealerValue << " against your " << playerValue << "." << endl;
        player.updateBankroll(-bet);
        player.getStats().recordLoss();
    }
    else {
        cout << "It's a tie with both at " << playerValue << "." << endl;
        player.getStats().recordPush();
    }

    player.getStats().setTotalMoney(player.getBankroll());

    cout << "New balance: " << player.getBankroll() << endl;
}

// Main game logic: initializes players, deals initial cards, manages turns, and evaluates results at the end
//game flow: 1) initialize players and deal initial cards, 2) players take turns, 3) dealer takes turn, 4) evaluate results
void BlackjackGame::startGame() {
    deck = Deck(); //fresh shuffled deck each round
    cout << "\n\nStarting the game..." << endl;

    for (auto& player : players) {
        player.clearHand();
    }

    dealersdeck.clear();
    dealerValue = 0;

    for (int i = 0; i < players.size(); i++) {
        int bet = 0;

        while (true) {
            cout << "\nPlayer " << players[i].getName()
                 << ", enter bet (available: "
                 << players[i].getBankroll() << "): ";
            cin >> bet;

            if (bet > 0 && bet <= players[i].getBankroll()) break;

            cout << "Invalid bet. Try again.\n";
        }

        players[i].setBet(bet);

        vector<string> cards = deck.drawCards(2);
        players[i].addToHand(cards);
        players[i].displayHand();
    }

    cout << "\n\nDealer's turn..." << endl;
    dealersdeck = deck.drawCards(2);
    cout << "Dealer shows: " << dealersdeck[0] << " [Hidden]" << endl;

    cout << "\n\nNow it's time for the players to take their turns!" << endl;
    PlayersTurn();

    cout << "\n\nNow it's time for the dealer's turn!" << endl;
    dealersTurn();

    cout << "\n\nLet's see who wins...\n" << endl;
    for (int i = 0; i < players.size(); i++) {
        cout << "Evaluating Player " << players[i].getName() << "..." << endl;

        if (players[i].hasSplitHand()) {
            vector<int> splitResults = players[i].getSplitResult();

            for (size_t j = 0; j < splitResults.size(); j++) {
                cout << "  Split hand " << (j + 1) << ": ";
                int playerValue = splitResults[j];
                ElevationLogic(players[i], playerValue, dealerValue);
            }
        } 
        else {
            int playerValue = players[i].getResult();
            ElevationLogic(players[i], playerValue, dealerValue);
        }
    }
}
