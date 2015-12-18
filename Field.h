#ifndef FIELD
#define FIELD



#include <iostream>
#include <assert.h>
#include <cstdlib>

#include "Chute.h"
#include "Transporter.h"
#include "Ladder.h"
#include "Player.h"


class Field {
public:
	int chuteCount;
	int ladderCount;
	int turn;

	Chute *chutes;
	Ladder *ladders;
	Player p1, p2;


	Field();
	~Field();

	int getStatus(int);
	bool play();
	void print();

};



#endif

