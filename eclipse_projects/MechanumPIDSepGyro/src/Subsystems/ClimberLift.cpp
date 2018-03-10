#include "ctre/Phoenix.h"
#include "../RobotMap.h"
#include "ClimberLift.h"
#include "../Commands/SetClimberLiftHeight.h"
ClimberLift::ClimberLift() : frc::Subsystem("ClimberLift") {//Change PID Values
    liftTalon = RobotMap::climberlift;
    ratchet =RobotMap::climberratchet;
    upperSwitch = RobotMap::climberliftswitchupper;
	lowerSwitch = RobotMap::climberliftswitchlower;
	startCounter = 0;
}

void ClimberLift::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    //SetDefaultCommand(new SetClimberLiftHeight());
}

void ClimberLift::Periodic() {
    // Put code here to be run every loop

}
void ClimberLift::SetSpeed(double speed){


	if(!(DeadBand(speed,0.15,-0.35,1)==0)){
		if(speed > 0){
			ratchet->Set(frc::Relay::Value::kOn);
			if(startCounter<3){
				startCounter++;
			}
			else{
				liftTalon->Set(speed);
			}
		}
		else{
			liftTalon->Set(speed);
			ratchet->Set(frc::Relay::Value::kOff);
		}

	}
	else{
		ratchet->Set(frc::Relay::Value::kOff);
		liftTalon->Set(0);
		startCounter = 0;
	}
}

double ClimberLift::DeadBand(double input, double band,double minimum, double maximum){
	if(input>maximum){
		input = maximum;
	}
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
