#include "ctre/Phoenix.h"
#include "../RobotMap.h"

#include "../Commands/AdjustGrabberHeight.h"
#include "GrabberLift.h"
GrabberLift::GrabberLift() : frc::PIDSubsystem("GrabberLift",0.0001,0,0,0) {//Change PID Values

    SetAbsoluteTolerance(0.01);
    GetPIDController()->SetContinuous(false);
    liftTalon = RobotMap::grabberlift;
	SetOutputRange(-1,0.45);//Change these values to change speed
	maxQuadPosition = -25000;
	upperSwitch =RobotMap::grabberliftswitchupper;
	lowerSwitch =RobotMap::grabberliftswitchlower;
	liftTalon->GetSensorCollection().SetQuadraturePosition(0,0);
	isEnabled = true;
	Enable();
}

void GrabberLift::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new AdjustGrabberLiftHeight());
}

void GrabberLift::Periodic() {
	if(lowerSwitch->Get()){
		liftTalon->GetSensorCollection().SetQuadraturePosition(0,10);
		if(GetSetpoint()>=0){
			liftTalon->Set(0);
		}
	}
	if (upperSwitch->Get()){
		maxQuadPosition = liftTalon->GetSensorCollection().GetQuadraturePosition();
		if(GetSetpoint()<maxQuadPosition){
			SetSetpoint(maxQuadPosition+300);
		}
	}
	//SmartDashboard::PutString("DB/String 7",std::to_string(upperSwitch->Get()));
	SmartDashboard::PutString("DB/String 5", std::to_string( liftTalon->GetSensorCollection().GetQuadraturePosition()));
}
double GrabberLift::DeadBand(double input, double band){
	if(input > band || input <-band){
		return input;
	}
	else{
		return 0;
	}
}

double GrabberLift::ReturnPIDInput() {
	return liftTalon->GetSensorCollection().GetQuadraturePosition();// returns the sensor value that is providing the feedback for the system
}
void GrabberLift::UsePIDOutput(double output) {
	liftTalon->Set(output-0.13);
	}

bool GrabberLift::AtSetpoint(){
	bool isNotMoving = (liftTalon->GetSensorCollection().GetQuadratureVelocity()<5&&liftTalon->GetSensorCollection().GetQuadratureVelocity()>-5);
	bool onTarget = (GetPosition()-GetSetpoint() < 1600 &&GetPosition()-GetSetpoint() > -1600);
	return isNotMoving && onTarget;
}

void GrabberLift::SetGroundHeight(){
	SetSetpoint(0);//Change to Right Position
}
void GrabberLift::SetSwitchHeight(){
	SetSetpoint(-10000);//Change to Right Position
}
void GrabberLift::SetMidHeight(){
	SetSetpoint(-16000);//Change to Right Position
}
void GrabberLift::SetHighHeight(){

	SetSetpoint(maxQuadPosition+100);//Change to Right Position
}
void GrabberLift::AdjustHeight(double modifier){
	if(!(DeadBand(modifier,0.15)==0)){
		Disable();
		if(upperSwitch->Get() && modifier>0){
			liftTalon->Set(modifier);
		}
		else if (lowerSwitch->Get() && modifier<0){
			liftTalon->Set(modifier);
		}
		else if (!lowerSwitch->Get() && !upperSwitch->Get()){
			liftTalon->Set(modifier);
		}
		else{
			liftTalon->Set(0);
		}
		isEnabled = false;
	}
	else{
		if(!isEnabled){
			liftTalon->Set(0);
			SetSetpoint(liftTalon->GetSensorCollection().GetQuadraturePosition());
			isEnabled = true;
			Enable();
		}
	}
}

void GrabberLift::ResetEncoders(){
	liftTalon->GetSensorCollection().SetQuadraturePosition(-20,0);
}
