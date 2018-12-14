/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Command.h>
#include "../Robot.h"

class DriveWithGyro : public frc::Command
{

public:

	DriveWithGyro(double _distance);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:

	double AnglePGain = 0.10, AngleIGain = 0.00000, AngleDGain = 0.003;
	double DrivePGain = 0.3, DriveIGain = 0.00003, DriveDGain = 0.003;
	double distance = 0;

	double DriveError = 0, AngleError = 0, DriveSetPoint = 0, AngleSetPoint = 0, AngleResultant = 0, DriveResultant = 0, DrivePreviousError = 0,
		   AnglePreviousError = 0, DriveIntegral = 0, AngleIntegral = 0, DriveDerivative = 0, AngleDerivative = 0;

	double currentX;
	double currentY;
	double initialAngle;
	double goalX;
	double goalY;
	double remainingDistance = 0;


};

