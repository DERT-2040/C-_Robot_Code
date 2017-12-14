#ifndef RightAuto_H
#define RightAuto_H

#include "../CommandBase.h"
#include "../Commands/VisionAuto.h"
#include "../Subsystems/DriveTrain.h"
#include "../Subsystems/Gears.h"
#include "WPILib.h"
#include "Timer.h"

class RightAuto : public CommandBase {
public:
	RightAuto();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	DriveTrain* drive = new DriveTrain;
	Gears* gear = new Gears;
	Timer timer;
	bool longStraight = false;
	bool rotate = false;
	bool shortStraight = false;
	bool gearDrop = false;
	int stage = 0;
};

#endif  // RightAuto_H
