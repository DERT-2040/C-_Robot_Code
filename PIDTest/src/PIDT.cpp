/*
 * PIDT.cpp
 *
 *  Created on: Jul 5, 2018
 *      Author: FIRSTMentor
 */

#include "PIDT.h"

PIDT::PIDT(float Px, float Ix, float Dx) {
	P = Px;
	I = Ix;
	D = Dx;

	error = 0;
	setpoint = 0;
	resultant = 0;
	integral = 0;
	derivative = 0;
	previous_error = 0;

}

void PIDT::setSetpoint(float setpoint)
{
	this->setpoint = setpoint;
}

double PIDT::runPID(double input)
{
	previous_error = error;

	error = setpoint - input;
	integral += (error*.02);
	derivative = (error-previous_error) / .02;
	resultant = P*error + I*integral + D*derivative;
	if(resultant > 1)
	{
		resultant = 1;
	}
	return resultant;

}

PIDT::~PIDT() {
	// TODO Auto-generated destructor stub
}

