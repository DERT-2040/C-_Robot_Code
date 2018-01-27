#ifndef ShootLeft_H
#define ShootLeft_H

#include "../CommandBase.h"
#include "../Subsystems/DriveTrain.h"
#include "../Subsystems/Shooter.h"
#include "../Subsystems/Gears.h"
class ShootLeft : public CommandBase {
public:
	ShootLeft();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	DriveTrain *drive = new DriveTrain();
	Shooter *shoot = new Shooter();
	Gears *gear = new Gears();
	Timer timer;

	bool orientation = false;
};

#endif  // ShootLeft_H
