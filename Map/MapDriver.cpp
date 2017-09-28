#include <iostream>
#include <vector>

#include "../Player/Player.h"
#include "Country.h"
#include "Map.h"

using namespace std;

int main() {
	Player *roosevelt = new Player("Teddy Roosevelt");
	Player *gandhi = new Player("Gandhi");

	vector<Country*> countries;
	countries.push_back(new Country("USA", "America", roosevelt, 10));
	countries.push_back(new Country("India", "Asia", gandhi, 20));
	countries.push_back(new Country("England", "Europe", roosevelt, 5));
	countries.push_back(new Country("China", "Asia", gandhi, 20));

	countries[0]->addBorderingCountry(countries[1]);
	countries[1]->addBorderingCountry(countries[0]);
	countries[1]->addBorderingCountry(countries[2]);
	countries[2]->addBorderingCountry(countries[1]);
	countries[2]->addBorderingCountry(countries[3]);
	countries[3]->addBorderingCountry(countries[2]);
	countries[3]->addBorderingCountry(countries[0]);
	countries[0]->addBorderingCountry(countries[3]);

	Map *world = new Map(countries);
	world->getCountries();

	for (auto& country : world->getCountries()) {
		cout << country->getName() << endl;
	}

	return 0;
}
