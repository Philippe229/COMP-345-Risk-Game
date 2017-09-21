/*
 * Hand.cpp
 *
 *  Created on: Sep 20, 2017
 *      Author: dylanfernandes
 */

#include "Hand.h"
#include <iostream>
using namespace std;

Hand::Hand(int max) {
	maxCards = max;
	numCards = 0;

}

void Hand::getCard(Card c)
{
	cards.push_back(c);
}

void Hand::PrintHand()
{
	Card::cardType type;
	cout << "Current Hand"<< endl;
	cout << "____________"<< endl;
	for(int i = 0;i < maxCards;i++)
	{
		if(!cards.empty() && i < cards.size())
		{
			type = cards.at(i).getCardVal();
			cout << "Card Slot " << i+1 << ": " << type << endl;
		}
		else
		{
			cout << "Card Slot " << i+1 << ": Empty Slot" << endl;
		}
	}
}

//if true, units will be given to player in the main driver
bool Hand::SelectExchange()
{
	int card1;
	int card2;
	int card3;
	PrintHand();
	if(numCards >= 3)
	{
		cout << "Select the three cards you wish to exchange" << endl;
		cout << "Select Card 1: ";
		cin >> card1;
		cout << "Select Card 2: ";
		cin >> card2;
		cout << "Select Card 3: ";
		cin >> card3;
		if(VerifyExchange(card1,card2,card3))
		{
			cards.erase(cards.begin() + card1-1);
			cards.erase(cards.begin() + card2-1);
			cards.erase(cards.begin() + card3-1);
			cout << "Successful exchange." << endl;
			return true;
		}
		else
		{
			cout << "Invalid exchange." << endl;
		}
	}
	else
		cout << "Not enough cards in hand to exchange" << endl;
	return false;
}

bool Hand::VerifyExchange(int c1, int c2, int c3)
{
	Card::cardType type1 = cards.at(c1-1).getCardVal(); //index starts at 0
	Card::cardType type2 = cards.at(c2-1).getCardVal();
	Card::cardType type3 = cards.at(c3-1).getCardVal();

	if(type1 == type2 && type2 == type3)  //same card type
	{
		return true;
	}
	if(type1 != type2 && type1 != type3 && type2 != type3) //unique card type
	{
		return true;
	}
	return false;
}

Hand::~Hand() {
	// TODO Auto-generated destructor stub
}

