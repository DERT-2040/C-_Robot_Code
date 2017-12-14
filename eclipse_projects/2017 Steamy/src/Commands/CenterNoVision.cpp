#include "CenterNoVision.h"

CenterNoVision::CenterNoVision() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CenterNoVision::Initialize() {
	SmartDashboard::PutString("DB/String 1", "Center Auto No Vision Init");
}

// Called repeatedly when this Command is scheduled to run
void CenterNoVision::Execute() {
	if (timer.Get() < 2.7){
		if(timer.Get() == 0)
			timer.Start();
		drive -> DriveStraight(.25);
	}else if (timer.Get() < 3.0){
		drive -> DriveStraight(.1);
	}else if (!gearDrop){
		drive -> Stop();
		gearDrop = gear -> GearDeploy();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool CenterNoVision::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CenterNoVision::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CenterNoVision::Interrupted() {

}
