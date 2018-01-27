#ifndef DudAuto_H
#define DudAuto_H

#include "../CommandBase.h"
#include "../Subsystems/DriveTrain.h"

class DudAuto : public CommandBase {
private:
	DriveTrain* fast = new DriveTrain();
	Timer timer;
public:
	DudAuto();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DudAuto_H
