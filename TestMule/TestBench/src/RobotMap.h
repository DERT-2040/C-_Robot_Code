#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "WPILib.h"
#include "ctre/Phoenix.h"


class RobotMap {
public:


	static std::shared_ptr<WPI_TalonSRX> FLDrive;
	static std::shared_ptr<WPI_TalonSRX> BLDrive;
	static std::shared_ptr<WPI_TalonSRX> FRDrive;
	static std::shared_ptr<WPI_TalonSRX> BRDrive;

	static void init();
};
#endif
