#include "ShootLeft.h"

ShootLeft::ShootLeft() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ShootLeft::Initialize() {
	SmartDashboard::PutString("DB/String 1", "ShootLeft Auto Init");
	orientation = false;
}

// Called repeatedly when this Command is scheduled to run
void ShootLeft::Execute() {
	if(timer.Get() < 1.0){
		if (timer.Get() == 0)
			timer.Start();
		shoot -> ShootWheelOnly();
	}else if (timer.Get() < 9.5){
		shoot -> Start();
	}else if (timer.Get() < 11.1){
		shoot -> Stop();
		drive -> DriveStraight(-.4);
	}else if (timer.Get() < 11.3){
		drive -> DriveStraight(-.1);
	}else if (timer.Get() < 11.7){
		drive -> Rotate(-.4);
	}else if (timer.Get() < 11.9){
		drive -> Rotate(-.1);
	}else if (timer.Get() < 13.1){
		drive -> DriveStraight(.4);
	} else if (timer.Get() < 13.4){
		drive -> Rotate(-.4);
	} else
		drive -> Stop();
}

// Make this return true when this Command no longer needs to run execute()
bool ShootLeft::IsFinished() {
	return orientation;
}

// Called once after isFinished returns true
void ShootLeft::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootLeft::Interrupted() {

}
