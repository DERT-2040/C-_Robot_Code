#include "ShootRight.h"

ShootRight::ShootRight() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ShootRight::Initialize() {
	SmartDashboard::PutString("DB/String 1", "ShootRight Auto Init");
	orientation = false;
}

// Called repeatedly when this Command is scheduled to run
void ShootRight::Execute() {
	if(timer.Get() < 1.0){
		if (timer.Get() == 0)
			timer.Start();
		shoot -> ShootWheelOnly();
	}else if (timer.Get() < 9.5){
		shoot -> Start();
	}else if (timer.Get() < 10.9){
		shoot -> Stop();
		drive -> DriveStraight(.4);
	}else if (timer.Get() < 11.1){
		drive -> DriveStraight(.1);
	}else if (timer.Get() < 11.4){
		drive -> Rotate(-.4);
	}else if (timer.Get() < 11.5){
		drive -> Rotate(-.1);
	}else if (timer.Get() < 11.9){
		drive -> Stop();
	}else if (!orientation){
		orientation = /*gear -> AutoVision();*/ true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ShootRight::IsFinished() {
	return orientation;
}

// Called once after isFinished returns true
void ShootRight::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootRight::Interrupted() {

}
