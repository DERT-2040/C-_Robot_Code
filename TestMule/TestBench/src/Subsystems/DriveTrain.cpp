#include "DriveTrain.h"
#include "../RobotMap.h"
#include "../Commands/JoystickDrive.h"
#include <ctre/Phoenix.h>
DriveTrain::DriveTrain() : frc::Subsystem("DriveTrain")
{

	FL = RobotMap::FLDrive;
	FR = RobotMap::FRDrive;
	BL = RobotMap::BLDrive;
	BR = RobotMap::BRDrive;
	IMU = RobotMap::IMU;
	tankDrive = new RobotDrive(FL, BL, FR, BR);
}

void DriveTrain::InitDefaultCommand()
{
	SetDefaultCommand(new drive());
}

void DriveTrain::resetEncoders()
{
	FL->GetSensorCollection().SetQuadraturePosition(0,0);
	//FR->GetSensorCollection().SetQuadraturePosition(0);
	//BL->GetSensorCollection().SetQuadraturePosition(0);
	BR->GetSensorCollection().SetQuadraturePosition(0,0);

}

void DriveTrain::Periodic()
{
	getEncoderValues();
	updatePosition();

}

void DriveTrain::tank()
{
	tankDrive->ArcadeDrive(Robot::oi->gamepad->GetRawAxis(1), Robot::oi->gamepad->GetRawAxis(4));
}

void DriveTrain::getEncoderValues(){
	//SmartDashboard::PutString("DB/String 0", std::to_string(FL->GetSensorCollection().GetQuadraturePosition()));
	SmartDashboard::PutString("DB/String 0", std::to_string(FL->GetSensorCollection().GetQuadraturePosition()));
	SmartDashboard::PutString("DB/String 1", std::to_string(-1*BR->GetSensorCollection().GetQuadraturePosition()));
	SmartDashboard::PutString("DB/String 3", std::to_string(IMU->GetVelocityX()));
	SmartDashboard::PutString("DB/String 4", std::to_string(IMU->GetVelocityY()));
	SmartDashboard::PutString("DB/String 5", std::to_string(IMU->GetYaw()));
	SmartDashboard::PutString("DB/String 6", std::to_string(IMU->GetAngle()));
}

void DriveTrain::updatePosition()
{
	double BRvelocity = -1*BR->GetSensorCollection().GetQuadratureVelocity()*ticksToFeet;
	double FLvelocity = FL->GetSensorCollection().GetQuadratureVelocity()*ticksToFeet;

	//driveTrainAngle += (BRvelocity - FLvelocity) * .20 / trackWidth;


	displacementX += (trackWidth * (BRvelocity+FLvelocity) / 2 * (BRvelocity - FLvelocity))
						* (sin((FLvelocity - BRvelocity) * .20 / trackWidth + IMU->GetYaw()) - sin(IMU->GetYaw()));

	displacementY -=  (trackWidth * (BRvelocity+FLvelocity) / 2 * (BRvelocity - FLvelocity))
							* (cos((FLvelocity - BRvelocity) * .20 / trackWidth + driveTrainAngle) - cos(IMU->GetYaw()));

	SmartDashboard::PutString("DB/String 7", std::to_string(displacementX));
	SmartDashboard::PutString("DB/String 8", std::to_string(displacementY));
	SmartDashboard::PutString("DB/String 9", std::to_string(driveTrainAngle));
}

