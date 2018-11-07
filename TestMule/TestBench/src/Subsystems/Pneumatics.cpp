#include "Pneumatics.h"
#include "../RobotMap.h"
Pneumatics::Pneumatics() : frc::Subsystem("DriveTrain")
{
	/*
	Comp = RobotMap::TestComp;
	Solenoid = RobotMap::TestSolenoid;
	Comp->SetClosedLoopControl(true);
	*/
}

void Pneumatics::InitDefaultCommand()
{

}

void Pneumatics::Periodic()
{


}

void Pneumatics::SetSolenoid(int power){//-1 for reverse, 0 for off, 1 for forward
	/*
	if (power == 1){
		Solenoid->Set(frc::DoubleSolenoid::Value::kForward);
	}
	else if (power == -1){
		Solenoid->Set(frc::DoubleSolenoid::Value::kReverse);
	}
	else{
		Solenoid->Set(frc::DoubleSolenoid::Value::kOff);

	}
	*/
}



