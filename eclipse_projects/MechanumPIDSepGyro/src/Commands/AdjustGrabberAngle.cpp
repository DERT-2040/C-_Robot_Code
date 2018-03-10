// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "AdjustGrabberAngle.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AdjustGrabberAngle::AdjustGrabberAngle(double powerI): frc::Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());

	Requires(Robot::grabber.get());
	speed = powerI;
	outputSpeed = speed;
}
void AdjustGrabberAngle::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AdjustGrabberAngle::Execute() {
	if(Robot::oi->getGamepad()->GetRawAxis(3)>0.75){
			outputSpeed=-0.5;
		}
		else if (speed == 0 && Robot::oi->getGamepad()->GetRawAxis(3)<0.1){
			outputSpeed = 0;
		}
		Robot::grabber->AdjustAngle(outputSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool AdjustGrabberAngle::IsFinished() {
	return false;

}

// Called once after isFinished returns true
void AdjustGrabberAngle::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AdjustGrabberAngle::Interrupted() {
}
