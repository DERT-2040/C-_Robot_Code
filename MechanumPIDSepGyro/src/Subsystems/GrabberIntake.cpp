#include "ctre/Phoenix.h"
#include "GrabberIntake.h"

#include "../Commands/SetIntakeWheelSpeed.h"
#include "../RobotMap.h"
GrabberIntake::GrabberIntake() : frc::Subsystem("GrabberIntake") {//Change PID Values

    wheelL = RobotMap::grabberintakeL;
    wheelR = RobotMap::grabberintakeR;


	wheelR->Set(ctre::phoenix::motorcontrol::ControlMode::Follower,9);
	//armR->SetInverted(true);//change to armL if arms aren't turning the right way
	//wheelR->SetInverted(true);//change to wheelL if wheels aren't turning the right way


    cubeSwitch = RobotMap::cubechecker;


	//angleY = 0;
}

void GrabberIntake::InitDefaultCommand() {
    // Set the default command for a subsystem here.
	SetDefaultCommand(new SetIntakeWheelSpeed(0));
}

void GrabberIntake::Periodic() {


}


void GrabberIntake::SetWheelSpeed(double speed){

	if(cubeSwitch->Get()&&speed>0){
		wheelL->Set(0);
	}
	else{
		wheelL->Set(speed);
	}
}

bool GrabberIntake::HasCube(){
	return cubeSwitch->Get();
}
/*double Grabber::InclinometerY() {
	int bits;
	inclinometerY->SetAverageBits(4);
	bits = inclinometerY->GetAverageBits();
	double averageVoltage = inclinometerY->GetAverageVoltage();
	angleY = (averageVoltage - 2.5) * 45;
	//angleY given in degrees
	return angleY;
}*/
