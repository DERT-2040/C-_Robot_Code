#ifndef CenterAuto_H
#define CenterAuto_H

#include "../CommandBase.h"
#include "../Commands/VisionAuto.h"
#include "../Subsystems/DriveTrain.h"
#include "../Subsystems/Gears.h"

#include <Timer.h>

class CenterAuto : public CommandBase {
public:
	CenterAuto();
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
	bool gearDrop = false;
	bool init = false;
};

#endif  // CenterAuto_H
