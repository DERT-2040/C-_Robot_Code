#ifndef CenterNoVision_H
#define CenterNoVision_H

#include "../CommandBase.h"
#include "../Commands/VisionAuto.h"
#include "../Subsystems/DriveTrain.h"
#include "../Subsystems/Gears.h"

#include <Timer.h>
class CenterNoVision : public CommandBase {
public:
	CenterNoVision();
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

#endif  // CenterNoVision_H
