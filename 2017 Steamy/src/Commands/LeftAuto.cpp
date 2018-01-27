#include "LeftAuto.h"

LeftAuto::LeftAuto() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void LeftAuto::Initialize() {
	SmartDashboard::PutString("DB/String 1", "Left Auto Init");
	drive -> ResetEncoders();
	longStraight = false;
	stage = 0;
	rotate = false;
	gearDrop = false;
}

// Called repeatedly when this Command is scheduled to run
void LeftAuto::Execute() {
	/*if (!longStraight){
		longStraight = drive -> EncodersStraight (18000, .4);
	}else if (stage == 0) { //Untested and taken out
		drive -> ResetEncoders();
		stage ++;
	}else if (!rotate){
		rotate = drive -> EncodersRotate (5000, .4);*/

	if (timer.Get() < 1.5){
		if (timer.Get() == 0)
			timer.Start();
		drive -> DriveStraight(.38);
	}else if (timer.Get() < 1.6){
		drive -> DriveStraight(.1);
	}else if (timer.Get() < 1.9){
		drive -> Rotate(.42);
	}else if (timer.Get() < 2){
		drive -> Rotate(.1);
	}else if (!gearDrop){
		drive -> Stop();
		gearDrop = gear -> AutoVision();
	}

}

// Make this return true when this Command no longer needs to run execute()
bool LeftAuto::IsFinished() {
	return (gearDrop);
}

// Called once after isFinished returns true
void LeftAuto::End() {
	drive -> ResetEncoders();
	longStraight = false;
	stage = 0;
	rotate = 0;
	shortStraight = false;
	gearDrop = false;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LeftAuto::Interrupted() {

}
