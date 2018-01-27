#ifndef Testing_H
#define Testing_H

#include "../CommandBase.h"
#include "../Subsystems/driveTrain.h"
#include "WPILib.h"
#include <Joystick.h>

class Testing : public CommandBase {
public:
	Testing();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	DriveTrain* drive = new DriveTrain;
	frc::Timer timer;

    Joystick *m_driveStick = new Joystick {0};
    Joystick *m_driveStick2 = new Joystick {1};
    Joystick *m_gamepad = new Joystick {2};

};

#endif  // Testing_H
