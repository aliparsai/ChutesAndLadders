/*
 * Shoot.cpp
 *
 *  Created on: Dec 18, 2015
 *      Author: perham
 */

#include "Chute.h"

bool Chute::operator==(const Chute& s)
												{
		return (s.sourcePosition == sourcePosition && s.targetPosition == targetPosition);
												}

void Chute::assignRandom()
{
	Transporter::assignRandom();

	while (sourcePosition < targetPosition)
		Transporter::assignRandom();
}
