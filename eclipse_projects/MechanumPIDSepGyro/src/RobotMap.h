// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef ROBOTMAP_H
#define ROBOTMAP_H

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "WPILib.h"
#include "ctre/Phoenix.h"
#include <AnalogGyro.h>
#include <ADXL345_I2C.h>
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
class RobotMap {
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	//static std::shared_ptr<frc::AnalogAccelerometer> drivetrainAnalogAccelerometer1;
	static std::shared_ptr<WPI_TalonSRX> drivetrainRF;
	static std::shared_ptr<WPI_TalonSRX> drivetrainRB;
	static std::shared_ptr<WPI_TalonSRX> drivetrainLF;
	static std::shared_ptr<WPI_TalonSRX> drivetrainLB;
	static std::shared_ptr<WPI_TalonSRX> grabberlift;

	static std::shared_ptr<WPI_TalonSRX> grabberintakeL;
	static std::shared_ptr<WPI_TalonSRX> grabberintakeR;
	static std::shared_ptr<WPI_TalonSRX> grabberactuatorL;
	static std::shared_ptr<WPI_TalonSRX> grabberactuatorR;
	static std::shared_ptr<WPI_TalonSRX> climberlift;
	static std::shared_ptr<frc::DigitalInput> climberliftswitchupper;
	static std::shared_ptr<frc::DigitalInput> climberliftswitchlower;
	static std::shared_ptr<frc::DigitalInput> grabberliftswitchupper;
	static std::shared_ptr<frc::DigitalInput> grabberliftswitchlower;
	static std::shared_ptr<frc::DigitalInput> grabberswitchupper;
	static std::shared_ptr<frc::DigitalInput> grabberswitchlower;
	static std::shared_ptr<frc::DigitalInput> cubechecker;

	static std::shared_ptr<frc::Relay> climberratchet;
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    static std::shared_ptr<frc::AnalogGyro> sensorsAnalogGyro1;
    static std::shared_ptr<frc::ADXL345_I2C> accel;
	static std::shared_ptr<frc::AnalogInput> sensorsUltrasonic;
	static std::shared_ptr<frc::AnalogInput> sensorsInclinometerX;
	static std::shared_ptr<frc::AnalogInput> sensorsInclinometerY;
	static void init();
};
#endif
