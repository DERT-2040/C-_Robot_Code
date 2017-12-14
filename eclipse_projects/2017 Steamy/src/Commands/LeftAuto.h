#ifndef LeftAuto_H
#define LeftAuto_H

#include "../CommandBase.h"
#include "../Commands/VisionAuto.h"
#include "../Subsystems/DriveTrain.h"
#include "../Subsystems/Gears.h"
#include "WPILib.h"
#include <Joystick.h>
#include "Timer.h"

class LeftAuto : public CommandBase {
public:
	LeftAuto();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	DriveTrain* drive = new DriveTrain;
	Gears* gear = new Gears;
	Timer timer;
	bool longStraight = true;
	bool rotate = false;
	bool shortStraight = false;
	bool gearDrop = false;
	int stage = 0;


};



#endif  // LeftAuto_H
