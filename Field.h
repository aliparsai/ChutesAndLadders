#include <iostream>
#include <assert.h>
#include <cstdlib>

#include "Transporter.h"
#include "Shoot.h"
#include "Ladder.h"
#include "Player.h"


class Field {
public:
	int shootCount;
	int ladderCount;
	int turn;

	Shoot *shoots;
	Ladder *ladders;
	Player p1, p2;


	Field();
	~Field();

	int getStatus(int);
	bool play();
	void print();

};



