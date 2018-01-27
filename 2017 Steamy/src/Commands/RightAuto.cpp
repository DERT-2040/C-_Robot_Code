#include "RightAuto.h"

RightAuto::RightAuto() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void RightAuto::Initialize() {
	SmartDashboard::PutString("DB/String 1", "Right Auto Init");
	drive -> ResetEncoders();
	longStraight = false;
	stage = 0;
	rotate = false;
	gearDrop = false;
}

// Called repeatedly when this Command is scheduled to run
void RightAuto::Execute() {
	/*if (!longStraight){
		longStraight = drive -> EncodersStraight (18000, .4);*/
	if (timer.Get() < 1.6){
		if (timer.Get() == 0)
			timer.Start();
		drive -> DriveStraight(.40);
	}else if (timer.Get() < 1.7){
		drive -> DriveStraight(.1);
	}else if (timer.Get() < 2.0){
		drive -> Rotate(-.4);
	}else if(timer.Get() < 2.1){
		drive -> Rotate(-.1);
	}else if (!gearDrop){
		drive -> Stop();
		gearDrop = gear -> AutoVision();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool RightAuto::IsFinished() {
	return (gearDrop);
}

// Called once after isFinished returns true
void RightAuto::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RightAuto::Interrupted() {

}
