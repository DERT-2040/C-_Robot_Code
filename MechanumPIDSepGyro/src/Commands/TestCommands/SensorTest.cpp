// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "SensorTest.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

SensorTest::SensorTest(): frc::Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. Requires(Robot::
	Requires(Robot::grabber.get());
	Requires(Robot::gyroSubsystem.get());
	Requires(Robot::drivetrain.get());
}
void SensorTest::Initialize() {
}

// Called repeatedly when tahis Command is scheduled to run
void SensorTest::Execute() {
	SmartDashboard::PutString("DB/String 0", std::to_string(Robot::grabber->Ultrasonic()));
	SmartDashboard::PutString("DB/String 1", std::to_string(Robot::grabber->InclinometerAngle()));
	SmartDashboard::PutString("DB/String 2", std::to_string(Robot::gyroSubsystem->gAngle()));
	SmartDashboard::PutString("DB/String 3", std::to_string(Robot::drivetrain->getAccelX()));
	SmartDashboard::PutString("DB/String 4", std::to_string(Robot::drivetrain->getAccelY()));
}

// Make this return true when this Command no longer needs to run execute()
bool SensorTest::IsFinished() {
	return false;

}

// Called once after isFinished returns true
void SensorTest::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SensorTest::Interrupted() {
}