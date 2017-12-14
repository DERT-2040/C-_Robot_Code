#include "OI.h"

#include <WPILib.h>

OI::OI() {
	// Process operator interface input here.
}

frc::Joystick* OI::GetJoystick() {
	return &joystick;
}

frc::Joystick* OI::GetJoystick2() {
	return &joystick2;
}
