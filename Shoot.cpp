/*
 * Shoot.cpp
 *
 *  Created on: Dec 18, 2015
 *      Author: perham
 */

#include "Shoot.h"

bool Shoot::operator==(const Shoot& s)
												{
		return (s.sourcePosition == sourcePosition && s.targetPosition == targetPosition);
												}

void Shoot::assignRandom()
{
	Transporter::assignRandom();

	while (sourcePosition < targetPosition)
		Transporter::assignRandom();
}
