// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.



#include "Position2R.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

Position2R::Position2R() : CommandGroup("2R")  {
	AddParallel(new SetGrabberLiftHeightAuto(1));
	AddSequential(new StopFromAccel());
	AddSequential(new SetGrabberAngleAuto(30));
	AddSequential(new SetIntakeWheelSpeedForTime(-1,0.3));
	AddParallel(new SetGrabberAngleAuto(0));
	AddSequential(new MoveMeters(-1));
	AddParallel(new SetGrabberLiftHeightAuto(0));
	AddSequential(new TurnDegrees(-90));
	//Deploy Box
 }
