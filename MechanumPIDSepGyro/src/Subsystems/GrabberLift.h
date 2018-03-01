#ifndef GRABBERLIFT_H
#define GRABBERLIFT_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class GrabberLift: public frc::PIDSubsystem{
private:
	std::shared_ptr<WPI_TalonSRX> liftTalon;
	double ReturnPIDInput() override;
	void UsePIDOutput(double output) override;
	int maxQuadPosition;
	std::shared_ptr<DigitalInput> upperSwitch;
	std::shared_ptr<DigitalInput> lowerSwitch;
public:
	GrabberLift();
	void InitDefaultCommand() override;
	void Periodic() override;
	double DeadBand(double input, double band);
	bool AtSetpoint();//Returns true if it is close to the target
	void SetGroundHeight();//Sets Lift to height on ground
	void SetSwitchHeight();//Sets Lift to the height of the switch
	void SetMidHeight();//Sets Lift to height of the scale at the middle section
	void SetHighHeight();//Sets Lift to height on the highest position of the scale
	void AdjustHeight(double modifier);//Adds or subtracts from the PID to adjust hieght
	void ResetEncoders();//Sets the encoder to zero
	bool isEnabled;
};

#endif
