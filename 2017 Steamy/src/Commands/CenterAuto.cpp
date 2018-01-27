#include "CenterAuto.h"

CenterAuto::CenterAuto() {
}

// Called just before this Command runs the first time
void CenterAuto::Initialize() {
	SmartDashboard::PutString("DB/String 1", "Center Auto Init");
	drive -> ResetEncoders();
	longStraight = false;
	gearDrop = false;
}

// Called repeatedly when this Command is scheduled to run
void CenterAuto::Execute() {
	/*if (!longStraight)
		longStraight = drive -> EncodersStraight(10000, .4);*/
	if (timer.Get() < .9){
		if(timer.Get() == 0)
			timer.Start();
		drive -> DriveStraight(.37);
	}else if (timer.Get() < 1.5){
		drive -> DriveStraight(.1);
	}else if (timer.Get() < 2.0){
		drive -> Stop();
	}else if (!gearDrop){
		gearDrop = gear -> AutoGears();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool CenterAuto::IsFinished() {
	return (gearDrop); // SEE IF THIS WORKS
}

// Called once after isFinished returns true
void CenterAuto::End() {
	SmartDashboard::PutString("DB/String 1", "Center Auto Finished");
	longStraight = false;
	gearDrop = false;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CenterAuto::Interrupted() {

}
