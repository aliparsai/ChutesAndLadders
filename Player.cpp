
#include "Player.h"

	Player::Player()
	{
		position = 0;
	}

	Player::Player(int num)
	{
		position = 0;
		std::stringstream buf;
		buf << "Player " <<  num;
		name = buf.str();
	}
