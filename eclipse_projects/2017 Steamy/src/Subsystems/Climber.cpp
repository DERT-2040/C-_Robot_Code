#include "Climber.h"
#include "../RobotMap.h"

Climber::Climber() : Subsystem("ExampleSubsystem") {

}

void Climber::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void Climber::Climb(bool button){
	if (button)
		climber.Set(1);
	else
		climber.Set(0);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
