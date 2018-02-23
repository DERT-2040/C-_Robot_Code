#include "ctre/Phoenix.h"
#include "../RobotMap.h"
#include "GrabberLift.h"
GrabberLift::GrabberLift() : frc::PIDSubsystem("ClawLift",0.001,0,0) {//Change PID Values

    SetAbsoluteTolerance(0.01);
    GetPIDController()->SetContinuous(false);
    liftTalon = RobotMap::grabberlift;
	SetOutputRange(-1,1);//Change these values to change speed
	maxQuadPosition = 7200;
	upperSwitch =RobotMap::grabberliftswitchupper;
	lowerSwitch =RobotMap::grabberliftswitchlower;
	liftTalon->GetSensorCollection().SetQuadraturePosition(0,0);
	Enable();
}

void GrabberLift::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
}

void GrabberLift::Periodic() {
	if(lowerSwitch->Get()){
		liftTalon->GetSensorCollection().SetQuadraturePosition(0,10);
		if(liftTalon->GetSensorCollection().GetQuadraturePosition()<0){
			SetSetpoint(300);
		}
	}
	if (upperSwitch->Get()){
		SmartDashboard::PutString("DB/String 5","AAAAAA");
		maxQuadPosition = -1*liftTalon->GetSensorCollection().GetQuadraturePosition();
		if(liftTalon->GetSensorCollection().GetQuadraturePosition()>maxQuadPosition-10 && GetSetpoint()>maxQuadPosition){
			SetSetpoint(maxQuadPosition-300);
		}
	}
	//SmartDashboard::PutString("DB/String 7",std::to_string(upperSwitch->Get()));
	SmartDashboard::PutString("DB/String 0", std::to_string(liftTalon->GetSensorCollection().GetQuadraturePosition()));


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
	return -1*liftTalon->GetSensorCollection().GetQuadraturePosition();// returns the sensor value that is providing the feedback for the system
}
void GrabberLift::UsePIDOutput(double output) {
	liftTalon->Set(output);
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
	SetSetpoint(2000);//Change to Right Position
}
void GrabberLift::SetMidHeight(){
	SetSetpoint(4000);//Change to Right Position
}
void GrabberLift::SetHighHeight(){

	SetSetpoint(maxQuadPosition-10);//Change to Right Position
}
void GrabberLift::AdjustHeight(double modifier){
	if(!(DeadBand(modifier,0.15)==0)){
		Disable();
		liftTalon->Set(modifier+0.25);
	}
	else{
		SetSetpoint(-1*liftTalon->GetSensorCollection().GetQuadraturePosition());
		Enable();
	}
	/*double rate = 0;//Change to rate of change wanted (modifier should be between -1 and 1)
	double actualModifier = modifier * rate;
	SetSetpoint(GetSetpoint()+actualModifier);*/
}
void GrabberLift::ResetEncoders(){
	liftTalon->GetSensorCollection().SetQuadraturePosition(-20,0);
}
