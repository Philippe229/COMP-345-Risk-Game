#include <iostream>
#include "Startup.h"

using namespace std;

int Startup::getUserInputInteger(string output, int min, int max) {
    int input;

    cout << output;
    cin >> input;

    while (input < min || input > max || cin.fail()) {
        if (input == -1) {
            cout << "Quitting..." << endl;
            exit(1);   
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input" << endl;
        cout << "Must be greater than " << min - 1 << " and less than " << max + 1 << " and must be an integer" << endl;
        cout << "Try again (-1 to quit): ";
        cin >> input;
    }

    return input;
}

void Startup::clearScreen() {
    cout << string(100, '\n');
}

void Startup::displayPlayersCountriesAndArmies(Player* thePlayer) {
    printf("%3s | %25s | %6s | %25s | %6s\n", "Num", "Country Owned", "Armies", "Bordering Countries", "Armies");
    for (int i = 0; i < thePlayer->getCountries().size(); i++) {
        Country* currCountry = thePlayer->getCountries()[i];
        printf("%3i | %25s | %6i | ", i + 1, currCountry->getName().c_str(), currCountry->getArmies());

        for (int j = 0; j < currCountry->getBorderingCountries().size(); j++) {
            Country* bordering = currCountry->getBorderingCountries()[j];
            if (j == 0) {
                printf("%25s | %6i\n", bordering->getName().c_str(), bordering->getArmies());
            } else {
                printf("%3s | %25s | %6s | %25s | %6i\n", "", "", "", bordering->getName().c_str(), bordering->getArmies());
            }
        }
    }
}

Startup::Startup(vector<Player*> players, Map* map) {
        playerOrder = players;
        currMap = map;
        randomPlayerOrder();
        assignCountries();
        assignArmies();
}

void Startup::randomPlayerOrder() {
    cout << endl << "*ASSIGNING RANDOM ORDER*" << endl;
    for (int i = 0; i < 100; i++) {
        int swapIndexOne = rand() % playerOrder.size();
        int swapIndexTwo = rand() % playerOrder.size();

        Player* tempPlayer = playerOrder[swapIndexOne];
        playerOrder[swapIndexOne] = playerOrder[swapIndexTwo];
        playerOrder[swapIndexTwo] = tempPlayer;
    }

    cout << endl << "Current player order: " << endl;
    for (int i = 0; i < playerOrder.size(); i++) {
        cout << (i + 1) << ": " << playerOrder[i]->getName() << endl;
    }
}

void Startup::assignCountries() {
    cout << endl << "*ASSIGNING RANDOM COUNTRIES TO PLAYERS*" << endl;
    int numCountriesAssigned = 0;
    int currPlayerIndex = 0;

    while (numCountriesAssigned < currMap->getCountries().size()) {
        int countryIndexToAssign = rand() % currMap->getCountries().size();

        if (currMap->getCountries()[countryIndexToAssign]->getOwner() == NULL) {
            numCountriesAssigned += 1;

            currMap->getCountries()[countryIndexToAssign]->setOwner(playerOrder[currPlayerIndex]);
            playerOrder[currPlayerIndex]->addCountry(currMap->getCountries()[countryIndexToAssign]);
            currPlayerIndex = (currPlayerIndex + 1) % playerOrder.size();
        }
    }
    
    cout << endl << "Current countries assigned: " << endl;
    for (int i = 0; i < playerOrder.size(); i++) {
        cout << endl << playerOrder[i]->getName() << "(" << playerOrder[i]->getCountries().size() << " countries): " << endl;
        for (int j = 0; j < playerOrder[i]->getCountries().size(); j++) {
            cout << playerOrder[i]->getCountries()[j]->getName() << endl;
        }
    }
}

void Startup::assignArmies() {
    cout << endl << "*ASSIGNING ARMIES TO COUNTRIES*" << endl;
    int numArmies[6] = {0, 40, 35, 30, 25, 20};
    int totalTokens = numArmies[playerOrder.size() - 1] * playerOrder.size();
    int currPlayerIndex = 0;
    map<string, int> playerArmies;

    for (int i = 0; i < playerOrder.size(); i++) {
        playerArmies[playerOrder[i]->getName()] = numArmies[playerOrder.size() - 1];
    }

    for (int i = 0; i < currMap->getCountries().size(); i++) {
        currMap->getCountries()[i]->addArmies(1);
        totalTokens -= 1;

        playerArmies[currMap->getCountries()[i]->getOwner()->getName()] -= 1;
    }

    while (totalTokens > 0) {
        Player* currPlayersTurn = playerOrder[currPlayerIndex];

        if (playerArmies[currPlayersTurn->getName()] > 0) {
            cout << endl << "Current player to place an army unit (" << playerArmies[currPlayersTurn->getName()] << " left): " << currPlayersTurn->getName() << endl;
            displayPlayersCountriesAndArmies(currPlayersTurn);
            int countryNumber = getUserInputInteger("Your choice (-1 to quit): ", 1, currPlayersTurn->getCountries().size());
            currPlayersTurn->getCountries()[countryNumber - 1]->addArmies(1);
            totalTokens -= 1;
            playerArmies[currPlayersTurn->getName()] -= 1;
        }

        currPlayerIndex = (currPlayerIndex + 1) % playerOrder.size();
    }
}

vector<Player*> Startup::getPlayerOrder() {
    return playerOrder;
}