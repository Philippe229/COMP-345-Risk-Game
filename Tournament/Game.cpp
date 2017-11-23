#include "Game.h"
#include "../GamePhases/MainLoop.h"
#include "../CardComponents/Deck.h"

Game::Game(Map* m, vector<Player*> p, int n, int max) {
	map = m;
	players = p;
	gameNumber = n;
	maxTurns = max;
}

void Game::startGame() {
	Deck* d = new Deck(map->getCountries().size());
	MainLoop mainLoop(players, map, d, maxTurns);
	int results = mainLoop.playSeveral();
	if (results == -1) {
		win = NULL;
	} else {
		for (auto& player : players) {
			if (player->getID() == results) {
				win = player;
			}
		}
	}

}

string Game::getWinnerName() {
	if(win == NULL)
		return "DRAW";
	else	
		return to_string(win->getID());
}