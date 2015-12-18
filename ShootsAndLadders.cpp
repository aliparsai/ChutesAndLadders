#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <assert.h>

using namespace std;



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


class Transporter {
public:
	int sourcePosition;
	int targetPosition;

	Transporter();
	void assignRandom();

};

Transporter::Transporter()
{
	sourcePosition = 0;
	targetPosition = 0;
}

void Transporter::assignRandom()
{
	sourcePosition = rand() % 100;
	targetPosition = rand() % 100;

	while(sourcePosition == targetPosition)
		targetPosition = rand() % 100;
}


class Shoot : public Transporter {
public:
	void assignRandom();
	bool operator==(const Shoot& s)
												{
		return (s.sourcePosition == sourcePosition && s.targetPosition == targetPosition);
												}

};

void Shoot::assignRandom()
{
	Transporter::assignRandom();

	while (sourcePosition < targetPosition)
		Transporter::assignRandom();
}



class Ladder : public Transporter {
public:
	void assignRandom();
	bool operator==(const Ladder& l)
												{
		return (l.sourcePosition == sourcePosition && l.targetPosition == targetPosition);
												}
};

void Ladder::assignRandom()
{
	Transporter::assignRandom();

	while (sourcePosition > targetPosition)
		Transporter::assignRandom();
}

class Player {
public:
	int position;
	string name;

	Player()
	{
		position = 0;
	}

	Player(int num)
	{
		position = 0;
		stringstream buf;
		buf << "Player" <<  num;
		name = buf.str();
	}

};

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
			cout << "Too bad! Snake bit you." << endl;
			return shoots[i].targetPosition;
		}
	}


	for(i=0; i<ladderCount; i++)
	{
		if(pos == ladders[i].sourcePosition)
		{
			cout << "Great! You climbed the ladder." << endl;
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

	cout << "Turn: " << player->name  << endl << "Dice: " << dice << endl;

	if (player->position == 100)
	{
		cout << player->name << " won!" << endl;
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
		cout << "---------------------------------------------------" << endl;

		for (j=0; j<10; j++)
		{
			if (i%2 == 0) k=j;
			else k=9-j;
			p = i*10 + k;

			if (p == p1.position)
				cout << "| \033[1;31mp1\033[0m " ;

			else if (p == p2.position)
				cout << "| \033[1;36mp2\033[0m " ;

			else
			{
				cout << "| " << p << " ";
				if (p < 10)
					cout << " ";
			}
		}
		cout << "|" << endl;

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
					cout << "| s" << l << " " ;
					f = true;
				}
				else if (p == shoots[l].targetPosition)
				{
					cout << "|*s" << l << " " ;
					f = true;
				}
			}

			for (l=0; l<ladderCount; l++)
			{
				if (p == ladders[l].sourcePosition)
				{
					cout << "| l" << l << " " ;
					f = true;
				}
				else if (p == ladders[l].targetPosition)
				{
					cout << "|*l" << l << " " ;
					f = true;
				}
			}

			if (!f)
			{
				cout << "|    ";
			}
		}
		cout << "|" << endl;




	}
	cout << "---------------------------------------------------" << endl;
}


int main(void) {
	srand(time(0));

	Field f;

	while(f.play())
	{
	f.print();
	cin.get();
	}

	return 0;
}
