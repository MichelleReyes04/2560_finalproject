#include <iostream>
#include <string>
#include <vector>
#include "blackjackGame.h"
#include "player.h"
#include "utils.h"
#include "scoreboard.h"
using namespace std;

int main() {
    cout << "\nWelcome to Blackjack!" << endl;

    int numPlayers;

    cout << "\nPlease enter the number of players: ";
    cin >> numPlayers;

    while (numPlayers <= 0) {
        cout << "Invalid number of players. Please enter a positive integer: ";
        cin >> numPlayers;
    }

    vector<Player> players;
    players.reserve(numPlayers);

    for (int i = 0; i < numPlayers; i++) {
        string name;
        cout << "Enter name for Player " << (i + 1) << ": ";
        cin >> name;

        players.emplace_back(name, 0);
    }

    Scoreboard scoreboard("scoreboard.txt");

    //load saved stats and balances if names already exist
    scoreboard.loadPlayers(players);

    int choice = 0;

    while (choice != 5) {
        cout << "\n===== Main Menu =====" << endl;
        cout << "1. Play Round" << endl;
        cout << "2. View Current Stats" << endl;
        cout << "3. View Scoreboard" << endl;
        cout << "4. Reset Current Session" << endl;
        cout << "5. Save and Quit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            clearScreen();
            BlackjackGame game(players);
            game.startGame();

            //save immediately after each round
            scoreboard.savePlayers(players);

            int afterRoundChoice = 0;

            while (afterRoundChoice != 4) {
                cout << "\n===== After Round Menu =====" << endl;
                cout << "1. Play Again" << endl;
                cout << "2. View Current Stats" << endl;
                cout << "3. View Scoreboard" << endl;
                cout << "4. Return to Main Menu" << endl;
                cout << "Enter choice: ";
                cin >> afterRoundChoice;

                if (afterRoundChoice == 1) {
                    clearScreen();
                    BlackjackGame nextGame(players);
                    nextGame.startGame();

                    //save after every new round
                    scoreboard.savePlayers(players);
                }
                else if (afterRoundChoice == 2) {
                    clearScreen();
                    cout << "\n===== Current Player Stats =====" << endl;

                    for (const auto& player : players) {
                        cout << "\nStats for " << player.getName() << ":" << endl;
                        player.displayStats();
                    }
                }
                else if (afterRoundChoice == 3) {
                    clearScreen();
                    scoreboard.displayScoreboard();
                }
                else if (afterRoundChoice == 4) {
                    cout << "\nReturning to main menu..." << endl;
                }
                else {
                    cout << "Invalid choice. Try again." << endl;
                }
            }
        }
        else if (choice == 2) {
            clearScreen();
            cout << "\n===== Current Player Stats =====" << endl;

            for (const auto& player : players) {
                cout << "\nStats for " << player.getName() << ":" << endl;
                player.displayStats();
            }
        }
        else if (choice == 3) {
            clearScreen();
            scoreboard.displayScoreboard();
        }
        else if (choice == 4) {
            cout << "\nResetting current session..." << endl;

            for (auto& player : players) {
                player.setBankroll(100);
                player.getStats().setStats(0, 0, 0, 0, 0, 100);
            }

            scoreboard.resetPlayers(players);

            cout << "Current players have been reset." << endl;
            clearScreen();
        }
        else if (choice == 5) {
            scoreboard.savePlayers(players);
            cout << "\nStats and balances saved." << endl;
            cout << "Thank you for playing Blackjack! Goodbye!" << endl;
        }
        else {
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}