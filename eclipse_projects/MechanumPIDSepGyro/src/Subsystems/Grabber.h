#ifndef GRABBER_H
#define GRABBER_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class Grabber: public frc::PIDSubsystem{
private:
	std::shared_ptr<WPI_TalonSRX> wheelL;
	std::shared_ptr<WPI_TalonSRX> wheelR;
	std::shared_ptr<WPI_TalonSRX> armL;
	std::shared_ptr<WPI_TalonSRX> armR;
	std::shared_ptr<frc::AnalogInput> ultrasonic;
	std::shared_ptr<frc::AnalogInput> inclinometerX;
	std::shared_ptr<frc::AnalogInput> inclinometerY;
	double ReturnPIDInput() override;
	void UsePIDOutput(double output) override;
	std::shared_ptr<DigitalInput> upperSwitch;
	std::shared_ptr<DigitalInput> lowerSwitch;
	std::shared_ptr<DigitalInput> cubeSwitch;

public:
	Grabber();
	void InitDefaultCommand() override;
	void Periodic() override;
	bool AtSetpoint();//Returns true if it is close to the target
	void SetWheelSpeed(double speed);//Sets wheel speed for intake (from -1 to 1)
	void SetAngle(double angle);//Sets angle for intake (from -10 to 80)
	double Ultrasonic();
	double InclinometerAngle();
	void AdjustAngle(double speed);
	bool HasCube();
	//double InclinometerY();
	double range;
	double angle;
	double minPosition;
	double maxPosition;
	//double angleY;

};

#endif
