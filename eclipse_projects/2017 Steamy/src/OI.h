#ifndef OI_H
#define OI_H

#include <Joystick.h>


class OI {
public:
	OI();
	frc::Joystick *GetJoystick();
	frc::Joystick *GetJoystick2();

private:
	frc::Joystick joystick {2}; //Unused. We might switch to this later
	frc::Joystick joystick2 {3};
};

#endif  // OI_H
