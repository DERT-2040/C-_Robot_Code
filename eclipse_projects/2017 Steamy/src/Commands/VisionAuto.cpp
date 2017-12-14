#include "VisionAuto.h"

VisionAuto::VisionAuto() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void VisionAuto::Initialize() {
	SmartDashboard::PutString("DB/String 1", "Vision Auto");
	visionDrive -> ResetEncoders();
}

// Called repeatedly when this Command is scheduled to run
void VisionAuto::Execute() {

	isFinished = visionGears -> AutoGears();
	//visionGears -> Openplease();
	//visionDrive -> EncodersRotate(5000,.4);
}

// Make this return true when this Command no longer needs to run execute()
bool VisionAuto::IsFinished() {
	return isFinished;
}

// Called once after isFinished returns true
void VisionAuto::End() {
	visionDrive -> Stop();

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VisionAuto::Interrupted() {
	visionDrive -> Stop();
}
