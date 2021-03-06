// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
#include "Commands/Subsystem.h"
#include "WPILib.h"


/**
 *
 *
 * @author ExampleAuthor
 */
class Drivetrain: public frc::PIDSubsystem{
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<frc::AnalogGyro> analogGyro1;
	std::shared_ptr<WPI_TalonSRX> rF;
	std::shared_ptr<WPI_TalonSRX> rB;
	std::shared_ptr<WPI_TalonSRX> lF;
	std::shared_ptr<WPI_TalonSRX> lB;
	RobotDrive *drive;
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
public:
	Drivetrain();
	void InitDefaultCommand() override;
	void Periodic() override;
	void driving(double xVal, double yVal, double zVal, double sensitivity,double gyroAngle);
	void driveMeters(double meters);
	double DeadBand(double input, double band);
	double getAccelX();
	double getAccelY();
	double getAccelZ();
	bool isMoving();
	double gAngle();
	double getGyroRate();
	void resetEncoders();
	bool isMovingWithAccelY();
	void setSpeed(double speedRF,double speedRB,double speedLF,double speedLB);
	void turnDegrees(double degrees);

	double ReturnPIDInput() override;
	void UsePIDOutput(double output) override;
	bool AtSetpoint();

	void SetBrakeMode(bool brake);
	void strafeRight();
	void strafeLeft();
	double rFmodifier = 0;
	double rBmodifier = 0;
	double lFmodifier = 0;
	double lBmodifier = 0;
	bool turning = false;
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
};

#endif
