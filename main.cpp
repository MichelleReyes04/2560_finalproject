#include <iostream>
#include <string>
#include <vector>
#include "blackjackGame.h"
#include "player.h"
#include "utils.h"
using namespace std;

int main() {
    //Ask user of they want to play, and if so, how many players and their names. Then start the game loop.
    cout << "\nDo you want to play Blackjack? (yes/no): ";
    string playGame;
    cin >> playGame;

    while (playGame == "yes") {

        int numPlayers;
     
        cout << "\nPlease enter the number of players (0 to quit): ";
        cin >> numPlayers;

        if (numPlayers == 0) {
            cout << "\nThank you for playing Blackjack! Goodbye!" << endl;
            break;
        }
        if (numPlayers < 0) {
            cout << "\nInvalid number of players. Please enter a positive integer." << endl;
            continue;
        }

        vector<string> names;
        names.reserve(numPlayers);

        for (int i = 0; i < numPlayers; i++) {
            string name;
            cout << "Enter name for Player " << (i + 1) << ": ";
            cin >> name;
            names.push_back(name);
        }

        ///////////////////Create game instance and start the game ///////////////////////
        BlackjackGame game(numPlayers, names);
        game.startGame();
        /////////////////////////////////////////

        cout << "\nDo you want to play again? (yes/no): ";
        cin >> playGame;

        if (playGame != "yes") {
            cout << "\nThank you for playing Blackjack! Goodbye!" << endl;
        }
    }

    return 0;
}
