#ifndef Gears_H
#define Gears_H

#include <Commands/Subsystem.h>
#include "../Subsystems/Targeting.h"
#include "../Subsystems/DriveTrain.h"
#include <Relay.h>
#include <DigitalInput.h>
#include "WPILib.h"
#include <SmartDashboard/SmartDashboard.h>
#include <ctre/Phoenix.h>

class Gears : public Subsystem {
private:
	phoenix::motorcontrol::can::WPI_TalonSRX talon{8};
	Timer timer;
	DigitalInput* endNO = new DigitalInput(1); //defines 4 digital inputs, for two limit switches
	DigitalInput* endNC = new DigitalInput(2); // NO = Normally open
	DigitalInput* startNO = new DigitalInput(3);   // NC = Normally closed
	DigitalInput* startNC = new DigitalInput(4);
	DigitalInput* pegNO = new DigitalInput(5);

	bool autoGears = false; //Name is questionable

	bool triggerHit = false;
	int state = 0;

	int status = 0;
	bool timerStatus = false;
	bool visionIn = false;

	int autoStage = 0;
	double offset = 1;
	double errorX = 0;
	double area = 0;
	bool targetSight = false;

	DriveTrain *gearDrive = new DriveTrain();
	Targeting *gearTarget = new Targeting();

public:
	Gears();
	void InitDefaultCommand();
	/**
	 * Opens and closes the gear holder with button toggles
	 */
	void AutoAction(bool inStart, bool inStop);
	/**
	 * Runs through the entire chain of commands neccesary to put a gear on a peg
	 * Returns true when finished
	 */
	bool AutoGears();
	bool AutoVision();
	bool GearDeploy();
	void ManualReverse(bool emergency);
	void TeleopGears(bool input, bool output);
	void Reset();
	void Openplease();


};

#endif  // Gears_H
