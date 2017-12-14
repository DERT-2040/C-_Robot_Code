#ifndef DriveTrain_H
#define DriveTrain_H
#include <CANTalon.h>
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
	CANTalon rf{1}; /*right front */
	CANTalon rr{2}; /*right rear */
	CANTalon lf{3}; /*left front */
	CANTalon lr{4};/*left rear */

	RobotDrive *drive = new RobotDrive {lf, lr, rf, rr};

	bool encodersCheck = false;
	int lfPWP = 0;
	int lrPWP = 0;
	int rrPWP = 0;
	int rfPWP = 0;
	int avgChange = 0;
	bool returnValue = false;

	int pulse = 0;



public:

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
