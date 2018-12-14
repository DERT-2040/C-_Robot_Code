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

	//Calculates the Goal X and Y position based on the Robots current position and how far it wants to travel in a straight line
	goalX = currentX + distance*sin(Robot::driveTrain->getGyroAngle() * M_PI/180);
	goalY = currentY + distance*cos(Robot::driveTrain->getGyroAngle() * M_PI/180);

	//goalX = currentX + 5;
	//goalY = currentY + 10;

	SmartDashboard::PutString("DB/String 0", std::to_string(goalX));
	SmartDashboard::PutString("DB/String 1", std::to_string(goalY));

	initialAngle = Robot::driveTrain->getGyroAngle();
}

// Called just before this Command runs the first time
void DriveWithGyro::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void DriveWithGyro::Execute()
{
	//updates the commands current robot position from the driveTrain
	currentX = Robot::driveTrain->getXPosition();
	currentY = Robot::driveTrain->getYPosition();

	//Driving Speed PID
	remainingDistance = sqrt(pow(goalX - currentX, 2) + pow(goalY - currentY, 2)); //Gets the remaining euclidean distance to goal
	DriveError = remainingDistance; //Calculates The error from the setpoint of the PID
	DriveIntegral += (DriveError*.02); //Integrates the error
	DriveDerivative = (DriveError - DrivePreviousError)/.02; //Finds the derivative of the error over the last two loops
	DriveResultant = DrivePGain*DriveError + DriveIGain*DriveIntegral + DriveDGain*DriveDerivative; //PID calculation
	DrivePreviousError = DriveError; //Sets the previous error to this loops error

	//Rotation PID
	//How the PID works is commented above
	//Updates the Angle SetPoint continuously to always track the goal
	AngleSetPoint = atan2((goalX - currentX),(goalY - currentY)) * 180/M_PI + 360;

	if(AngleSetPoint > 360)
	{
		AngleSetPoint -= 360;
	}

	AngleError = AngleSetPoint - Robot::driveTrain->getGyroAngle();

	//Allows for the angle pid to be continous over a [0,360] range.
	if(AngleError > 180)
	{
		AngleError = AngleError - 360;
	}
	else if(AngleError < -180)
	{
		AngleError = 360 + AngleError;
	}

	AngleIntegral += (AngleError*.02);
	AngleDerivative = (AngleError - AnglePreviousError)/.02;
	AngleResultant = AnglePGain*AngleError + AngleIGain*AngleIntegral + AngleDGain*AngleDerivative;
	AnglePreviousError = AngleError;

	Robot::driveTrain->autoDrive(DriveResultant, -1*AngleResultant); //Calls the drive train autoDrive function with the DrivePID and AnglePID resultants

	SmartDashboard::PutString("DB/String 2", std::to_string(currentX));
	SmartDashboard::PutString("DB/String 3", std::to_string(currentY));
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithGyro::IsFinished()
{
	if(remainingDistance < .05)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Called once after isFinished returns true
void DriveWithGyro::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithGyro::Interrupted()
{

}
