#ifndef Climber_H
#define Climber_H

#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>

class Climber : public Subsystem {
private:
	phoenix::motorcontrol::can::WPI_TalonSRX climber{5};
	bool status = false;

public:
	Climber();
	void InitDefaultCommand();
	/**
	 * Button is set to (A) on the controller to activate the motor on the climber
	 * Button has to be held
	 */
	void Climb(bool button);
};

#endif  // Climber_H
