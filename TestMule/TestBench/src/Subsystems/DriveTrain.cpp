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
	tankDrive->SetMaxOutput(.50);
	xOffset = .45;
	yOffset = -.38;
	displacementY = yOffset;
	displacementX = xOffset;
}

void DriveTrain::InitDefaultCommand()
{
	SetDefaultCommand(new drive());
	IMU->Reset();
}

void DriveTrain::displayValues(double goalX,double goalY,double DriveError,double AngleError){


}

void DriveTrain::resetEncoders()
{
	FL->GetSensorCollection().SetQuadraturePosition(0,0);
}

void DriveTrain::Periodic()
{
	//getEncoderValues();
	updatePosition();
	SmartDashboard::PutString("DB/String 9", std::to_string(IMU->GetYaw()));
	SmartDashboard::PutString("DB/String 2", std::to_string(displacementX));
	SmartDashboard::PutString("DB/String 3", std::to_string(displacementY));
}

double DriveTrain::getXPosition()
{
	return displacementX;
}

double DriveTrain::getYPosition()
{
	return displacementY;
}

void DriveTrain::tank()
{
	tankDrive->ArcadeDrive(-1*Robot::oi->gamepad->GetRawAxis(1), -1*Robot::oi->gamepad->GetRawAxis(4), false);
}

void DriveTrain::getEncoderValues(){
	SmartDashboard::PutString("DB/String 0", std::to_string(FL->GetSensorCollection().GetQuadraturePosition()));
	SmartDashboard::PutString("DB/String 1", std::to_string(-1*BR->GetSensorCollection().GetQuadraturePosition()));
	SmartDashboard::PutString("DB/String 5", std::to_string(IMU->GetYaw()));
}

void DriveTrain::updatePosition()
{
	displacementX += (-1*FL->GetSensorCollection().GetQuadraturePosition()+previousPos)*ticksToFeet * sin(IMU->GetYaw() * M_PI/180);
	displacementY += (-1*FL->GetSensorCollection().GetQuadraturePosition()+previousPos)*ticksToFeet * cos(IMU->GetYaw() * M_PI/180);
	previousPos = FL->GetSensorCollection().GetQuadraturePosition();
}

void DriveTrain::autoDrive(double speed, double omega)
{
	tankDrive->ArcadeDrive(speed, omega, false);
}

double DriveTrain::getGyroAngle()
{
	double angle;
	angle = IMU->GetYaw() + 360;
	if(angle > 360)
	{
		angle -= 360;
	}

	return (angle);
}

void DriveTrain::resetDisplacement()
{
	displacementY = 0;
	displacementX = 0;
	resetEncoders();
	previousPos = 0;
}

std::shared_ptr<AHRS> DriveTrain::getIMU()
{
	return IMU;
}




