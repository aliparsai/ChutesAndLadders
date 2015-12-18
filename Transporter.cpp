/*
 * Transporter.cpp
 *
 *  Created on: Dec 18, 2015
 *      Author: perham
 */

#include "Transporter.h"


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
