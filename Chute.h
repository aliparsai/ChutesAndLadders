#ifndef CHUTE
#define CHUTE

#include "Transporter.h"

class Chute : public Transporter {
public:
	void assignRandom();
	bool operator==(const Chute&);
};


#endif
