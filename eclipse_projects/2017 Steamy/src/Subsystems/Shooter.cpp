#include "Shooter.h"
#include "../RobotMap.h"

Shooter::Shooter() : Subsystem("ExampleSubsystem") {

}

void Shooter::InitDefaultCommand() {

}

void Shooter::Start() {
	shooter.Set(.7);
	feeder.Set(-1);
}

void Shooter::Stop(){
	shooter.Set(0);
	feeder.Set(0);
}


void Shooter::Shoot(bool button0, bool button1) {
	if (button0)
		status = true;
	if (button1)
		status = false;

	if (status){
		Start();
	}else{
		Stop();
	}
}

void Shooter::FeederOnly(){
	feeder.Set(-1);
}

void Shooter::ShootWheelOnly(){
	shooter.Set(.7);
}
