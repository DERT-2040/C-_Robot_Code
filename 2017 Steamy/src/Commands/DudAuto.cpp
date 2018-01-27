#include "DudAuto.h"

DudAuto::DudAuto() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void DudAuto::Initialize() {
	timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void DudAuto::Execute() {
	if (timer.Get() < 4.0){		fast -> DriveStraight(.3);
	}else{
		fast -> Stop();
	}

}

// Make this return true when this Command no longer needs to run execute()
bool DudAuto::IsFinished() {
	if (timer.Get() > 4.5)
		return true;
	else
		return false;
}

// Called once after isFinished returns true
void DudAuto::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DudAuto::Interrupted() {

}
