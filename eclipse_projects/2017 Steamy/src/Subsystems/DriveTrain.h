#ifndef DriveTrain_H
#define DriveTrain_H
#include <ctrlib/CANTalon.h>
#include <RobotDrive.h>
#include "WPILib.h"
#include <memory>
#include <Commands/Subsystem.h>
#include "../OI.h"
#include <RobotDrive.h>
#include <PIDController.h>
#include <Servo.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>



class DriveTrain : public Subsystem {
private:
	//Create an object for each motor. The number corresponds to CAN value
	CANTalon rf{1}; /*right front */
	CANTalon rr{2}; /*right rear */
	CANTalon lf{3}; /*left front */
	CANTalon lr{4};/*left rear */
	//Creates an object that combines all the motor into one to make it easier to use
	RobotDrive *drive = new RobotDrive {lf, lr, rf, rr};

	//Variables that were used to work with encoders. Doesn't really work
	bool encodersCheck = false;
	int lfPWP = 0;
	int lrPWP = 0;
	int rrPWP = 0;
	int rfPWP = 0;
	int avgChange = 0;
	bool returnValue = false;

	int pulse = 0;



public:
	//Everytime you add a program to the .cpp, you MUST declare it here as this is what every other program will see

	//Format is: (Data type) (Command name) (Parameters separated by commas with varible types)
	DriveTrain();
	void InitDefaultCommand();
	void DriveStraight(double speed);
	void Strafe(double speed);
	void Rotate(double speed);
	void PulseRotate(double speed);
	void Stop();
	double DeadBand(double input, double band);
	void UserCamera(int direction);
	void Teleop(double xVal, double yVal, double zVal, double sensitivity, bool toggleButton, int POV);
	void ResetEncoders();
	bool EncodersStraight(int distance, double speed);
	bool EncodersRotate(int rotation, double speed);
	bool EncodersTest(int distance, double speed);
	double GetAverageChange();



};

#endif  // DriveTrain_H
