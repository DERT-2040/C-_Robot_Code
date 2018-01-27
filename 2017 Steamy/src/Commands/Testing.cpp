#include "Testing.h"
#include "../Subsystems/DriveTrain.h"
#include "../Subsystems/Shooter.h"
#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>



Testing::Testing() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void Testing::Initialize() {
	timer.Reset();
	timer.Start();

	SmartDashboard::PutString("DB/String 3", "Initialized");
}

// Called repeatedly when this Command is scheduled to run
void Testing::Execute() {
	SmartDashboard::PutString("DB/String 3", "Exe Testing");
	//drive -> Teleop(m_driveStick -> GetX(), m_driveStick -> GetY(), m_driveStick2 -> GetZ());
	if (timer.Get() < 3.0)
		drive -> DriveStraight(.5);
	else if (timer.Get() < 6.0)
		drive -> Rotate(.5);
	else if (timer.Get() < 9.0)
		drive -> Strafe(.5);
	else
		drive -> Stop();
}

// Make this return true when this Command no longer needs to run execute()
bool Testing::IsFinished() {
	if (timer.Get() > 10.0)
		return true;
	else
		return false;
}

// Called once after isFinished returns true
void Testing::End() {
	SmartDashboard::PutString("DB/String 3", "Ending");
	drive->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Testing::Interrupted() {
	SmartDashboard::PutString("DB/String 3", "Interrupt");
}
