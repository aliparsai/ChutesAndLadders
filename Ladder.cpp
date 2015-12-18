
#include "Ladder.h"

bool Ladder::operator==(const Ladder& l)
{
	return (l.sourcePosition == sourcePosition && l.targetPosition == targetPosition);
}

void Ladder::assignRandom()
{
	Transporter::assignRandom();

	while (sourcePosition > targetPosition)
		Transporter::assignRandom();
}
