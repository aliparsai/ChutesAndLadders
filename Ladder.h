#ifndef LADDER
#define LADDER


#include "Transporter.h"

class Ladder : public Transporter {
public:
	void assignRandom();
	bool operator==(const Ladder&);
};


#endif
