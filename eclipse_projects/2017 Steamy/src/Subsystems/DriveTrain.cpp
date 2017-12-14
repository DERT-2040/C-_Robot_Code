#include "DriveTrain.h"
#include "../RobotMap.h"
#include "../Subsystems/Targeting.h"

#include "WPILib.h"
#include <iostream>
#include <string>
#include <memory>
#include <RobotDrive.h>
#include <Joystick.h>
#include <cmath>


DriveTrain::DriveTrain() : Subsystem("ExampleSubsystem") {

}

void DriveTrain::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());

    drive->SetInvertedMotor(RobotDrive::kFrontLeftMotor,true);
    drive->SetInvertedMotor(RobotDrive::kRearLeftMotor,true);
    drive->SetSafetyEnabled(false);
    ResetEncoders();
}

void DriveTrain::DriveStraight(double speed){
	drive -> MecanumDrive_Cartesian(0,-speed,0);
	SmartDashboard::PutString("DB/String 5", "Straight");
}

void DriveTrain::Strafe(double speed){
	drive->MecanumDrive_Cartesian(speed,0,0);
	SmartDashboard::PutString("DB/String 5", "Strafe");
}

void DriveTrain::Rotate(double speed){
	drive->MecanumDrive_Cartesian(0,0,speed);
	SmartDashboard::PutString("DB/String 5", "Rotate");
}

void DriveTrain::PulseRotate(double speed){
	if (pulse == 0){
	drive->MecanumDrive_Cartesian(0,0,speed);
		SmartDashboard::PutString("DB/String 5", "Pulse Rotate");
	}else if(pulse == 24){
		pulse = -1;
	}
	pulse++;
}

void DriveTrain::Stop(){
	drive->MecanumDrive_Cartesian(0,0,0);
	SmartDashboard::PutString("DB/String 5", "Stopped");
}

double DriveTrain::DeadBand(double input, double band){
	if (input > band || input < -band)
		return input;
	else
		return 0;
}

void DriveTrain::Teleop(double xVal, double yVal, double zVal, double sensitivity, bool toggleButton, int POV){

	sensitivity = (sensitivity - 1) / -2; //The z-axis on the controller goes from -1 (UP) to 1 DOWN

	drive->MecanumDrive_Cartesian(sensitivity * (DeadBand(xVal,0.15)),
							      sensitivity * (DeadBand(yVal,0.15)),
								  sensitivity * (DeadBand(zVal,0.15)));
	SmartDashboard::PutString("DB/String 5", "Teleop");
	/*
	if(!toggleButton){
		if (DeadBand(std::abs(xVal), 0.05) >= DeadBand(std::abs(yVal), 0.05))
				camera.Set(0.5);
		else if (std::abs(yVal)/yVal == 1)
				camera.Set(0);
		else
				camera.Set(1);
	}
	else*/
		//UserCamera(POV);

	ResetEncoders();
}

void DriveTrain::ResetEncoders(){
	lf.SetPulseWidthPosition(0);
	lr.SetPulseWidthPosition(0);
	rr.SetPulseWidthPosition(0);
	rf.SetPulseWidthPosition(0);
}

bool DriveTrain::EncodersStraight(int distance, double speed){ //make sure to reset encoders first

	returnValue = false;

	if (!encodersCheck && GetAverageChange() > 2000) //Making sure its reset within accpetance
		ResetEncoders();
	else if (!encodersCheck) //Double checks
		encodersCheck = true;
	else{
		avgChange = GetAverageChange();
		SmartDashboard::PutString("DB/String 7", std::to_string(avgChange)); //Troubleshooting
		if ((avgChange) < std::abs(distance * 4/5)){ //Goes full speed for 4/5
			DriveStraight(speed);
		}else if((avgChange) < (std::abs(distance))){ //Slows down
			DriveStraight(.2);
		}else{
			Stop();
			ResetEncoders();
			encodersCheck = false;
			returnValue = true;
		}
	}
	return returnValue;
	SmartDashboard::PutString("DB/String 6", "EncodersStraight");
}

bool DriveTrain::EncodersRotate(int rotation, double speed) { //make sure to reset encoders first
	returnValue = false;

	if (!encodersCheck && GetAverageChange() > 1000) //Making sure the encoders are reset within some acceptance
		ResetEncoders();
	else if (!encodersCheck) //Changes it to true if its already reset. Gives a check off
		encodersCheck = true;
	else{
		avgChange = GetAverageChange();
		SmartDashboard::PutString("DB/String 7", std::to_string(avgChange)); //Troubleshooting
		if (avgChange< std::abs(rotation * 4/5)) //Only goes full speed for a portion
			Rotate(speed);
		else if (avgChange < std::abs(rotation)) //Slows down
			Rotate (.2);
		else{
			Stop();
			ResetEncoders();
			encodersCheck = false;
			returnValue = true;
		}
	}
	return returnValue;
	SmartDashboard::PutString("DB/String 6", "EncodersRotate");
}


double DriveTrain::GetAverageChange() {
	lfPWP = std::abs(lf.GetPulseWidthPosition());
	lrPWP = std::abs(lr.GetPulseWidthPosition());
	rrPWP = std::abs(rr.GetPulseWidthPosition());
	rfPWP = std::abs(rf.GetPulseWidthPosition());
	return (lfPWP + lrPWP + rrPWP + rfPWP)/4;
}


// Put methods for controlling this subsystem
// here. Call these from Commands.
