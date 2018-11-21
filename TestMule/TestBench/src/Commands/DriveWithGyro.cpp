/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DriveWithGyro.h"
#include "../Subsystems/DriveTrain.h"

DriveWithGyro::DriveWithGyro(double _distance)
{
	Requires(Robot::driveTrain.get());

	distance = _distance;
	currentX = Robot::driveTrain->getXPosition();
	currentY = Robot::driveTrain->getYPosition();

	goalX = currentX - distance*sin(Robot::driveTrain->getGyroAngle() * M_PI/180);
	goalY = currentY - distance*cos(Robot::driveTrain->getGyroAngle() * M_PI/180);
	SmartDashboard::PutString("DB/String 6", std::to_string(goalX));
	SmartDashboard::PutString("DB/String 7", std::to_string(goalY));

	initialAngle = Robot::driveTrain->getGyroAngle();
	DriveSetPoint = 0;
	AngleSetPoint = initialAngle;
}

// Called just before this Command runs the first time
void DriveWithGyro::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void DriveWithGyro::Execute()
{
	currentX = Robot::driveTrain->getXPosition();
	currentY = Robot::driveTrain->getYPosition();
	remainingDistance = sqrt(pow(goalX - currentX, 2) + pow(goalY - currentY, 2));
	AngleSetPoint = tan((goalX - currentX)/(goalY - currentY));
	SmartDashboard::PutString("DB/String 4", std::to_string(remainingDistance));
	DriveError = DriveSetPoint - remainingDistance;
	DriveIntegral += (DriveError*.02);
	DriveDerivative = (DriveError - DrivePreviousError)/.02;
	DriveResultant = DrivePGain*DriveError + DriveIGain*DriveIntegral + DriveDGain*DriveDerivative;
	SmartDashboard::PutString("DB/String 2", std::to_string(DriveResultant));

	DrivePreviousError = DriveError;

	AngleError = AngleSetPoint - Robot::driveTrain->getGyroAngle();
	AngleIntegral += (AngleError*.02);
	AngleDerivative = (AngleError - AnglePreviousError)/.02;
	AngleResultant = AnglePGain*AngleError + AngleIGain*AngleIntegral + AngleDGain*AngleDerivative;
	AnglePreviousError = AngleError;

	Robot::driveTrain->autoDrive(DriveResultant, AngleResultant);

}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithGyro::IsFinished() {
	if(abs(remainingDistance) < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Called once after isFinished returns true
void DriveWithGyro::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithGyro::Interrupted() {

}
