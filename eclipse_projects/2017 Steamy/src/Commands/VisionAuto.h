#ifndef VisionAuto_H
#define VisionAuto_H

#include "../CommandBase.h"
#include "../Subsystems/Targeting.h"
#include "../Subsystems/DriveTrain.h"
#include "../Subsystems/Gears.h"

class VisionAuto : public CommandBase {
private:
	DriveTrain* visionDrive = new DriveTrain();
	Targeting* visionSystem = new Targeting();
	Gears* visionGears = new Gears();

	bool status = false;
	bool isFinished = false;

	int stage = 0;

public:
	VisionAuto();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // VisionAuto_H
