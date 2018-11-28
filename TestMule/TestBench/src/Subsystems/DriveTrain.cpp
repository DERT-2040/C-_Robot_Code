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
	displacementY = 0;
	displacementX = 0;
	SmartDashboard::PutString("DB/String 8", std::to_string(0));
	SmartDashboard::PutString("DB/String 9", std::to_string(0));
}

void DriveTrain::InitDefaultCommand()
{
	SetDefaultCommand(new drive());
	IMU->Reset();
}

void DriveTrain::displayValues(double goalX,double goalY,double DriveError,double AngleError){
	SmartDashboard::PutNumber("displacementX",displacementX);
	SmartDashboard::PutNumber("displacementY",displacementY);
	SmartDashboard::PutNumber("Left Encoder",FL->GetSensorCollection().GetQuadraturePosition());
	SmartDashboard::PutNumber("Right Encoder",-1*BR->GetSensorCollection().GetQuadraturePosition());
	SmartDashboard::PutNumber("Angle",IMU->GetYaw());
	SmartDashboard::PutNumber("Goal X",goalX);
	SmartDashboard::PutNumber("Goal Y",goalY);
	SmartDashboard::PutNumber("DriveError",DriveError);
	SmartDashboard::PutNumber("AngleError",AngleError);

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
	tankDrive->ArcadeDrive(Robot::oi->gamepad->GetRawAxis(1), Robot::oi->gamepad->GetRawAxis(4));
}

void DriveTrain::getEncoderValues(){
	SmartDashboard::PutString("DB/String 0", std::to_string(FL->GetSensorCollection().GetQuadraturePosition()));
	SmartDashboard::PutString("DB/String 1", std::to_string(-1*BR->GetSensorCollection().GetQuadraturePosition()));
	SmartDashboard::PutString("DB/String 5", std::to_string(IMU->GetYaw()));
	//SmartDashboard::PutString("DB/String 6", std::to_string(IMU->GetAngle()));
}

void DriveTrain::updatePosition()
{
	displacementX += (FL->GetSensorCollection().GetQuadraturePosition()-previousPos)*ticksToFeet * sin(IMU->GetYaw() * M_PI/180);
	displacementY += (FL->GetSensorCollection().GetQuadraturePosition()-previousPos)*ticksToFeet * cos(IMU->GetYaw() * M_PI/180);
	previousPos = FL->GetSensorCollection().GetQuadraturePosition();
	SmartDashboard::PutString("DB/String 8", std::to_string(displacementX));
	SmartDashboard::PutString("DB/String 9", std::to_string(displacementY));
}

void DriveTrain::autoDrive(double speed, double omega)
{
	tankDrive->ArcadeDrive(speed, omega, false);
}

double DriveTrain::getGyroAngle()
{
	return (IMU->GetYaw());
}




