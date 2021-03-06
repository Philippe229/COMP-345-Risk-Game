/*
 * PhaseObserverDriver.cpp
 *
 *  Created on: Nov 9, 2017
 *      Author: Philippe
 */

#include <ctime>
#include <iostream>
#include <vector>
#include "../Player/Player.h"
#include "../Player/PlayerStrategies/Human.h"
#include "../Map/Map.h"
#include "../MapLoader/MapLoader.h"
#include "../Map/Country.h"
#include "../Common/Common.h"
#include "../CardComponents/Deck.h"
#include "../GamePhases/MainLoop.h"

int main() {
	srand(time(0));

	// Load map, create deck, create player, assign countries
	MapLoader loader("./Map/maps/World(small).map");
	Map* map = loader.getMap();

    Deck* deck = new Deck(map -> getCountries().size());

	Player* player1 = new Human("Player 1");
	Player* player2 = new Human("Player 2");
	vector<Player*> players;
	players.push_back(player1);
	players.push_back(player2);

	for (auto& country : map -> getCountries()) {
		country -> addArmies(1);
		if ((&country - &*(map -> getCountries().begin())) % 2 == 0) {
			country -> setOwner(player1);
			player1 -> addCountry(country);
		} else {
			country -> setOwner(player2);
			player2 -> addCountry(country);
		}
	}

	// Start game
    MainLoop mainLoop(players, map, deck);
    mainLoop.play();


// Debug
//	cout << "Player 1" << endl;
//	Common::displayPlayersCountriesAndArmies(player1);
//
//	cout << endl << "Player 2" << endl;
//	Common::displayPlayersCountriesAndArmies(player2);

	delete player1;
	delete player2;
	delete deck;

	return 0;
}


