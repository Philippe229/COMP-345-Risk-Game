#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <string>
#include <vector>
#include "../Map/Country.h"
#include "../CardComponents/Hand.h"
#include "../CardComponents/Card.h"
#include "../DiceRollingFacility/DiceRollingFacility.h"

using namespace std;

//forward declaration (circular dependency)
class Country;

class Player {

private:
	string name;
	int unplaced_armies;
	static int nextID;
	int id;
	vector<Country*> countries;
	vector<Country*> attackBase;
	vector<Country*> attackPossibilities;
	DiceRollingFacility* dices;
	Hand* hand;
	void updateAttack();
	void attackProcedure();
	bool isContained(Country*,vector<Country*>);

public:
	Player();
	~Player();
	Player(string);
	Player(string, vector<Country*>);

	string getName();
	int getArmies();
	int getID();
	vector<Country*> getCountries();
	Country* getCountry(string name);
	void addArmies(int newArmies); // armies to be placed
	void addCountry(Country* c);
	void removeCountry(Country* c);
	void addArmiesToCountry(int, Country*);
	void removeArmiesFromCountry(int, Country*);
	void rollDie(); // for a1 demo
	void showCards(); // for a1 demo

	// 4. each player has: reinforce(), attack(), fortify() interface;
	void reinforce();
	void attack();
	void fortify();
};

#endif
