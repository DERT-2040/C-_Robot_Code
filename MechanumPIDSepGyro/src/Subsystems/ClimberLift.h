#ifndef CLIMBERLIFT_H
#define CLIMBERLIFT_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class ClimberLift: public frc::Subsystem{
private:
	std::shared_ptr<WPI_TalonSRX> liftTalon;
	std::shared_ptr<frc::Relay> ratchet;
	std::shared_ptr<DigitalInput> upperSwitch;
	std::shared_ptr<DigitalInput> lowerSwitch;

public:
	ClimberLift();
	void InitDefaultCommand() override;
	void Periodic() override;
	void SetSpeed(double speed);//Sets the encoder to zero
	bool AtTopLimit();
	bool AtBottomLimit();
	double DeadBand(double input, double band);


};

#endif
