/*
 * Hand.h
 *
 *  Created on: Sep 20, 2017
 *      Author: dylanfernandes
 */

#ifndef HAND_H_
#define HAND_H_
#include "Card.h"
#include <vector>

class Hand {
public:
	Hand(int);
	virtual ~Hand();
	bool SelectExchange();
	bool VerifyExchange(int, int, int);
	void PrintHand();
	void getCard(Card);
private:
	vector<Card> cards;
	int numCards;
	int maxCards;
};

#endif /* HAND_H_ */
