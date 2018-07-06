/*
 * PIDT.h
 *
 *  Created on: Jul 5, 2018
 *      Author: FIRSTMentor
 */

#ifndef SRC_PIDT_H_
#define SRC_PIDT_H_

class PIDT {
public:
	PIDT(float P, float I, float D);

	double runPID(double input);

	void setSetpoint(float setpoint);
	virtual ~PIDT();
private:
	float P , I , D, error, setpoint, resultant, integral,
	derivative, previous_error;
};

#endif /* SRC_PIDT_H_ */
