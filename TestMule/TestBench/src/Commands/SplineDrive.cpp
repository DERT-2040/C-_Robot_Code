/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SplineDrive.h"
#include "../Subsystems/DriveTrain.h"

SplineDrive::SplineDrive(std::vector<std::vector<double>> _spline) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());

	spline = _spline;
	goalY = 0;
	goalX = 0;
	initialAngle = 0;
	currentY = 0;
	currentX = 0;
	splineCounter = 0;
	distanceToEnd = sqrt(pow(spline[spline.size()-1][0] - currentX, 2) + pow(spline[spline.size()-1][1] - currentY, 2));
	previousX = 0;
	previousY = 0;
}

// Called just before this Command runs the first time
void SplineDrive::Initialize() {
	splineCounter = 0;
}

// Called repeatedly when this Command is scheduled to run
void SplineDrive::Execute()
{
	//Sets the current goal x and y location equal to the current spline point in the array
	if(splineCounter < spline.size())
    {
		goalX = spline[splineCounter][0];
		goalY = spline[splineCounter][1];
	}

	//updates the commands current robot position from the driveTrain
	currentX = Robot::driveTrain->getXPosition();
	currentY = Robot::driveTrain->getYPosition();

	/*
	 * Finds the euclidean distance to the end point of the spline from the current robot x and y. This could cause issues
	 * if the spline doubles back on itself. The proper way to do it would be calculated the distance between each point on the
	 * spline and add them up to get the curve length of the spline. This could be processor intensive and slow down the program
	 * depnding on how many points there are. A heuristic approach might be better.
	 */
	distanceToEnd = sqrt(pow(spline[spline.size()-1][0] - currentX, 2) + pow(spline[spline.size()-1][1] - currentY, 2));

	remainingDistance = sqrt(pow(goalX - currentX, 2) + pow(goalY - currentY, 2)); //calculates the remaining euclidean distance to the current x and y goal

	//Driving Speed PID

	DriveError = distanceToEnd; //Calculates The error from the setpoint of the PID
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

	/*
	 * The goal here is to Lower the drive resultant based on how high the Angle error is. This currently causes issues and needs
	 * further testing.
	 */
	DriveResultant = DriveResultant*(1-abs(AngleError)/180);

	Robot::driveTrain->autoDrive(DriveResultant, -1*AngleResultant); //Calls the drive train autoDrive function with the DrivePID and AnglePID resultants


	/*
	 * This aims to solve the problem of skipping over the tolerance range for meeting a point on the spline because of the RoboRIO's
	 * clock cycle being relatively slow. It takes the current x and y velocity, found by taking the derivative of the current and last location,
	 * then integrates them over steps of 10ms starting at 5ms into the future. Each loop it tests to see if the robot is within range of the spline point
	 * and if it is increment the splineCounter and break.
	 *
	 * This appeared to solve the problem, but im not sure if the code is actually working. When the velocities are put to SmartDashboard
	 * they show up as all 0s, but when the command finishes the velocities pop up.
	 */
	double currentXVelocity = (currentX - previousX)/0.02;
	double currentYVelocity = (currentY - previousY)/0.02;
	//SmartDashboard::PutString("DB/String 7", std::to_string(currentXVelocity));
	SmartDashboard::PutString("DB/String 1", std::to_string(currentYVelocity));
	for(double i = .005; i <= 0.040; i+=0.010)
	{
		double futureX = currentX + currentXVelocity*i;
		double futureY = currentY + currentYVelocity*i;

		if(sqrt(pow(goalX - futureX, 2) + pow(goalY - futureY, 2)) < distanceTolerance && splineCounter < spline.size() - 1)
		{
			splineCounter++;
			break;
		}
	}

	//If the robot is in range of a point(thats not the last one) increment the counter by 1
	if(remainingDistance < distanceTolerance && splineCounter < spline.size()-1)
	{
		splineCounter++;
	}

	//Sets the previous position for the next cycle
	previousX = currentX;
	previousY = currentY;

	SmartDashboard::PutString("DB/String 0", std::to_string(splineCounter));
}

// Make this return true when this Command no longer needs to run execute()
bool SplineDrive::IsFinished()
{
		//If the robot is within a tolerance range of the final point on the spline return true
		if(sqrt(pow(spline[spline.size()-1][0] - currentX, 2) + pow(spline[spline.size()-1][1] - currentY, 2)) < distanceTolerance)
		{
			return true;
		}
		else
		{
			return false;
		}
}

// Called once after isFinished returns true
void SplineDrive::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SplineDrive::Interrupted() {

}
