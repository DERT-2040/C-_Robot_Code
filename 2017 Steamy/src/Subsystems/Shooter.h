#ifndef Shooter_H
#define Shooter_H

#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include "WPILib.h"

class Shooter : public Subsystem {
private:
	phoenix::motorcontrol::can::WPI_TalonSRX shooter{6};
	phoenix::motorcontrol::can::WPI_TalonSRX feeder{7};
	bool status = false;
public:
	Shooter();
	void InitDefaultCommand();
	void Start();
	void Stop();
	void FeederOnly();
	void ShootWheelOnly();
	/**
	 * Button1 is set to (R1) and starts the shooter motor
	 * Button2 is set to (L1) and reverses the shooter motor
	 */
	void Shoot(bool button0, bool button1);
};

#endif  // Shooter_H
