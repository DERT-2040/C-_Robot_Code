#ifndef GRABBERINTAKE_H
#define GRABBERINTAKE_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class GrabberIntake: public frc::Subsystem{
private:
	std::shared_ptr<WPI_TalonSRX> wheelL;
	std::shared_ptr<WPI_TalonSRX> wheelR;
	std::shared_ptr<DigitalInput> cubeSwitch;

public:
	GrabberIntake();
	void InitDefaultCommand() override;
	void Periodic() override;
	void SetWheelSpeed(double speed);//Sets wheel speed for intake (from -1 to 1)
	bool HasCube();
	//double InclinometerY();
	//double angleY;

};

#endif
