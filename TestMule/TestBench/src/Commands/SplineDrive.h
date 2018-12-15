/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Command.h>
#include "../Robot.h"

class SplineDrive : public frc::Command
{

	public:

		SplineDrive(std::vector<std::vector<double>> _spline);
		void Initialize() override;
		void Execute() override;
		bool IsFinished() override;
		void End() override;
		void Interrupted() override;

	private:

		std::vector<std::vector<double>> spline;
		int splineWidth = 2;

		double AnglePGain = 0.15, AngleIGain = 0.010, AngleDGain = 0.005;
		double DrivePGain = 0.33, DriveIGain = 0.004, DriveDGain = 0.003;
		double distance = 0;

		double DriveError = 0, AngleError = 0, DriveSetPoint = 0, AngleSetPoint = 0, AngleResultant = 0, DriveResultant = 0, DrivePreviousError = 0,
			   AnglePreviousError = 0, DriveIntegral = 0, AngleIntegral = 0, DriveDerivative = 0, AngleDerivative = 0;

		double currentX;
		double currentY;
		double previousX;
		double previousY;
		double initialAngle;
		double goalX;
		double goalY;
		double distanceTolerance = .1;
		double remainingDistance = 0;
		int splineCounter = 0;
		double distanceToEnd;


};

