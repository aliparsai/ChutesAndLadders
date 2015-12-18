#include "Field.h"


int main(void) {
	srand(time(0));

	Field f;

	while(f.play())
	{
	f.print();
	std::cin.get();
	}

	return 0;
}
