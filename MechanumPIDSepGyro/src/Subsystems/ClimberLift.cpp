#include "ctre/Phoenix.h"
#include "../RobotMap.h"
#include "ClimberLift.h"
#include "../Commands/SetClimberLiftHeight.h"
ClimberLift::ClimberLift() : frc::Subsystem("ClimberLift") {//Change PID Values
    liftTalon = RobotMap::climberlift;
    ratchet =RobotMap::climberratchet;
    upperSwitch = RobotMap::climberliftswitchupper;
	lowerSwitch = RobotMap::climberliftswitchlower;
}

void ClimberLift::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    SetDefaultCommand(new SetClimberLiftHeight());
}

void ClimberLift::Periodic() {
    // Put code here to be run every loop

}
void ClimberLift::SetSpeed(double speed){


	if(!(DeadBand(speed,0.15)==0)){

		if(speed > 0){
			ratchet->Set(frc::Relay::Value::kOn);
			liftTalon->Set(speed);
		}
		else{
			ratchet->Set(frc::Relay::Value::kOff);
			liftTalon->Set(speed);
		}

	}
	else{
		ratchet->Set(frc::Relay::Value::kOff);
		liftTalon->Set(0);
	}
}

double ClimberLift::DeadBand(double input, double band){
	if(input > band || input <-band){
		return input;
	}
	else{
		return 0;
	}
}

bool ClimberLift::AtTopLimit(){
	if(upperSwitch->Get())
		SetSpeed(0);
	return upperSwitch->Get();
}
bool ClimberLift::AtBottomLimit(){
	if(lowerSwitch->Get())
		SetSpeed(0);
	return lowerSwitch->Get();
}
