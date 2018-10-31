#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <AHRS.h>

class RobotMap {
public:


	static std::shared_ptr<WPI_TalonSRX> FLDrive;
	static std::shared_ptr<WPI_TalonSRX> BLDrive;
	static std::shared_ptr<WPI_TalonSRX> FRDrive;
	static std::shared_ptr<WPI_TalonSRX> BRDrive;
	static std::shared_ptr<AHRS> IMU;

	static void init();
};
#endif
