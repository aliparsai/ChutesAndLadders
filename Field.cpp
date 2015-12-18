
#include "Field.h"


template <class T>
bool checkDuplicate(T* array, int dim, T newItem)
{
	int i;

	if (dim < 1)
		return false;

	for (i=0; i<dim; i++)
		if (array[i] == newItem)
			return true;

	return false;
}








Field::Field()
{

	int i;
	int *sourcePositions;
	int *targetPositions;

	turn = 1;
	shootCount = 5;
	ladderCount = 4;

	p1 = Player(1);
	p2 = Player(2);

	shoots = new Shoot [shootCount];
	ladders = new Ladder [ladderCount];
	sourcePositions = new int [shootCount+ladderCount];
	targetPositions = new int [shootCount+ladderCount];

	for(i=0; i<shootCount; i++)
	{
		shoots[i].assignRandom();
		sourcePositions[i] = shoots[i].sourcePosition;
		targetPositions[i] = shoots[i].targetPosition;

		while(checkDuplicate<int>(sourcePositions,i,sourcePositions[i]) || checkDuplicate<int>(targetPositions,i,targetPositions[i]))
		{
			shoots[i].assignRandom();
			sourcePositions[i] = shoots[i].sourcePosition;
			targetPositions[i] = shoots[i].targetPosition;
		}
	}


	for(i=0; i<ladderCount; i++)
	{
		ladders[i].assignRandom();
		sourcePositions[shootCount + i] = ladders[i].sourcePosition;
		targetPositions[shootCount + i] = ladders[i].targetPosition;

		while(checkDuplicate<int>(sourcePositions,shootCount+i,sourcePositions[shootCount+i]) || checkDuplicate<int>(targetPositions,shootCount+i,targetPositions[shootCount+i]))
		{
			ladders[i].assignRandom();
			sourcePositions[shootCount + i] = ladders[i].sourcePosition;
			targetPositions[shootCount + i] = ladders[i].targetPosition;

		}
	}

	delete[] sourcePositions;
	delete[] targetPositions;

}

Field::~Field()
{
	delete[] shoots;
	delete[] ladders;
}


int Field::getStatus(int pos)
{
	int i;

	if (pos >= 99) return 100;

	for(i=0; i<shootCount; i++)
	{
		if(pos == shoots[i].sourcePosition)
		{
			std::cout << "Too bad! Snake bit you." << std::endl;
			return shoots[i].targetPosition;
		}
	}


	for(i=0; i<ladderCount; i++)
	{
		if(pos == ladders[i].sourcePosition)
		{
			std::cout << "Great! You climbed the ladder." << std::endl;
			return ladders[i].targetPosition;
		}
	}

	return pos;
}


bool Field::play()
{
	Player *player;
	int dice;

	if (turn == 1)
		player = &p1;

	else if (turn == 2)
		player = &p2;

	else
		assert(false);

	turn = 3 - turn;
	dice = 1 + rand() % 6;

	player->position = getStatus(player->position + dice);

	std::cout << "Turn: " << player->name  << std::endl << "Dice: " << dice << std::endl;

	if (player->position == 100)
	{
		std::cout << player->name << " won!" << std::endl;
		return false;
	}


	return true;
}

void Field::print()
{
	int i,j,k,l,p;
	bool f = false;

	for (i=9; i>=0; i--)
	{
		std::cout << "---------------------------------------------------" << std::endl;

		for (j=0; j<10; j++)
		{
			if (i%2 == 0) k=j;
			else k=9-j;
			p = i*10 + k;

			if (p == p1.position)
				std::cout << "| \033[1;31mp1\033[0m " ;

			else if (p == p2.position)
				std::cout << "| \033[1;36mp2\033[0m " ;

			else
			{
				std::cout << "| " << p << " ";
				if (p < 10)
					std::cout << " ";
			}
		}
		std::cout << "|" << std::endl;

		for (j=0; j<10; j++)
		{
			f = false;
			if (i%2 == 0) k=j;
			else k=9-j;

			p = i*10 + k;

			for (l=0; l<shootCount; l++)
			{
				if (p == shoots[l].sourcePosition)
				{
					std::cout << "| s" << l << " " ;
					f = true;
				}
				else if (p == shoots[l].targetPosition)
				{
					std::cout << "|*s" << l << " " ;
					f = true;
				}
			}

			for (l=0; l<ladderCount; l++)
			{
				if (p == ladders[l].sourcePosition)
				{
					std::cout << "| l" << l << " " ;
					f = true;
				}
				else if (p == ladders[l].targetPosition)
				{
					std::cout << "|*l" << l << " " ;
					f = true;
				}
			}

			if (!f)
			{
				std::cout << "|    ";
			}
		}
		std::cout << "|" << std::endl;




	}
	std::cout << "---------------------------------------------------" << std::endl;
}

