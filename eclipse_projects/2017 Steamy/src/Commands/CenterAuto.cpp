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
	//Removed because it didn't work
	if (timer.Get() < .9){ //From 0 to 0.8 seconds (essentially run for .9 secs), run this segment
		if(timer.Get() == 0) //Makes sure that the timer is started
			timer.Start();
		drive -> DriveStraight(.37); //Drives robot forward with (double) speed from 0 to 1
	}else if (timer.Get() < 1.5){ //Run for .6 secs (1.5 - .9)
		drive -> DriveStraight(.1);
	}else if (timer.Get() < 2.0){
		drive -> Stop();
	}else if (!gearDrop){
		gearDrop = gear -> AutoGears(); //Vision segment and gear placement. Returns either bool False or True
	}
}

// Make this return true when this Command no longer needs to run execute()
bool CenterAuto::IsFinished() {
	return (gearDrop); // When gearDrop is bool True, end the command
}

// Called once after gearDrop returns true
void CenterAuto::End() {
	SmartDashboard::PutString("DB/String 1", "Center Auto Finished");
	longStraight = false;
	gearDrop = false;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CenterAuto::Interrupted() {

}
