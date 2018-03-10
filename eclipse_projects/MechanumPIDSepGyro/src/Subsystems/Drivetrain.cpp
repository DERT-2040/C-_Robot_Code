// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "ctre/Phoenix.h"

#include <iostream>
#include "Drivetrain.h"
#include "../RobotMap.h"
#include "../Commands/JoystickDrivetrain.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Drivetrain::Drivetrain() : frc::PIDSubsystem("Drivetrain",0.00007,0.0000000,0.00009) {

    //SetAbsoluteTolerance(0);
    GetPIDController()->SetContinuous(false);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    rF = RobotMap::drivetrainRF;
    rB = RobotMap::drivetrainRB;
    lF = RobotMap::drivetrainLF;
    lB = RobotMap::drivetrainLB;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	drive = new RobotDrive(lF, lB, rF, rB);

	drive->SetInvertedMotor(frc::RobotDrive::kFrontLeftMotor,true);
	drive->SetInvertedMotor(frc::RobotDrive::kFrontRightMotor,false);
	drive->SetInvertedMotor(frc::RobotDrive::kRearRightMotor,false);
	drive->SetInvertedMotor(frc::RobotDrive::kRearLeftMotor,true);

	//lB->SetInverted(true);
	/*rF->SetNeutralMode(Brake);
	rB->SetNeutralMode(Brake);
	lF->SetNeutralMode(Brake);
	lB->SetNeutralMode(Brake);*/
	SetOutputRange(-0.6,0.6);
}

void Drivetrain::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new JoystickDrivetrain());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Drivetrain::Periodic() {
    // Put code here to be run every loop
	SmartDashboard::PutString("DB/String 7",std::to_string(getAccelX()));

}

void Drivetrain::driving(double xVal, double yVal, double zVal, double sensitivity,double gyroAngle = 0.0) {
	//Disable();
	sensitivity = (sensitivity -1/-2);
	drive -> MecanumDrive_Cartesian(sensitivity*(DeadBand(xVal, 0.15)),sensitivity*(DeadBand(yVal, 0.15)),sensitivity*(DeadBand(zVal, 0.15)),gyroAngle);

	/*SmartDashboard::PutString("DB/String 5",std::to_string(rF->GetSensorCollection().GetQuadratureVelocity()));
	SmartDashboard::PutString("DB/String 6",std::to_string(rB->GetSensorCollection().GetQuadratureVelocity()));
	SmartDashboard::PutString("DB/String 7",std::to_string(lF->GetSensorCollection().GetQuadratureVelocity()));
	SmartDashboard::PutString("DB/String 8",std::to_string(lB->GetSensorCollection().GetQuadratureVelocity()));*/
}
void Drivetrain::driveMeters(double meters){
	turning = false;
	double metToTicks = 5506;

	double degrees=meters*metToTicks;
	Robot::gyroSubsystem->setDegrees(Robot::gyroSubsystem->gAngle());
	SetSetpoint(degrees);
	Enable();
	/*rB->Set(ctre::phoenix::motorcontrol::ControlMode::Follower,rF->GetDeviceID());
	lB->Set(ctre::phoenix::motorcontrol::ControlMode::Follower,rF->GetDeviceID());
		lF->Set(ctre::phoenix::motorcontrol::ControlMode::Follower,rF->GetDeviceID());


		rF->Set(ControlMode::Position, degrees);
		SmartDashboard::PutString("DB/String 4",std::to_string(rF->GetClosedLoopError(0)));


		SmartDashboard::PutString("DB/String 3",std::to_string(rF->GetMotorOutputPercent()));
		SmartDashboard::PutString("DB/String 7",std::to_string(degrees));
		SmartDashboard::PutString("DB/String 9",std::to_string(rF->GetSelectedSensorPosition(0)));*/
}
double Drivetrain::DeadBand(double input, double band){
	if(input > band || input <-band){
		return input;
	}
	else{
		return 0;
	}
}
double Drivetrain::getAccelX(){
	double accelX = RobotMap::accel -> GetX()*9.80;
	SmartDashboard::PutString("DB/String 5",std::to_string(accelX));
	return accelX;
}
double Drivetrain::getAccelY(){
	double accelY = RobotMap::accel -> GetY()*9.80;
	return accelY;
}
double Drivetrain::getAccelZ(){
	double accelZ = RobotMap::accel -> GetZ()*9.80;

	return accelZ;
}
bool Drivetrain::isMoving(){
	return (rF->GetMotorOutputPercent() < -0.001 || rF->GetMotorOutputPercent() > 0.001)&&(rF->GetClosedLoopError(0)-rF->GetClosedLoopTarget(0)>20 || rF->GetClosedLoopError(0)-rF->GetClosedLoopTarget(0)<-20) ;
}
void Drivetrain::resetEncoders(){
	rF->GetSensorCollection().SetQuadraturePosition(0,0);
	lF->GetSensorCollection().SetQuadraturePosition(0,0);
	lB->GetSensorCollection().SetQuadraturePosition(0,0);
	rB->GetSensorCollection().SetQuadraturePosition(0,0);
}

bool Drivetrain::isMovingWithAccelY(){
	return getAccelX()>-10;
}
void Drivetrain::setSpeed(double speedRF,double speedRB,double speedLF,double speedLB){
	Disable();
	rF->Set(speedRF);
	rB->Set(speedRB);
	lF->Set(speedLF);
	lB->Set(speedLB);
}

double Drivetrain::ReturnPIDInput() {
	return rB->GetSensorCollection().GetQuadraturePosition(); // returns the sensor value that is providing the feedback for the system
}
void Drivetrain::turnDegrees(double degrees){
	Robot::gyroSubsystem->setDegrees(degrees);
	//Enable();
	//turning = true;
	double modifier = Robot::gyroSubsystem->GetModifier();
	rF->PIDWrite(-modifier);
	rB->PIDWrite(-modifier);
	lF->PIDWrite(modifier);
	lB->PIDWrite(modifier);
	SmartDashboard::PutString("DB/String 8","Still Going");
}
void Drivetrain::turnToCube(){
	//Enable();
	//turning = true;
	double modifier = Robot::communication->GetModifier();
	/*rF->PIDWrite(modifier+0.3);
	rB->PIDWrite(modifier+0.3);
	lF->PIDWrite(-modifier+0.3);
	lB->PIDWrite(-modifier+0.3);*/

}
void Drivetrain::UsePIDOutput(double output) {
	double modifier = Robot::gyroSubsystem->GetModifier();
	SmartDashboard::PutString("DB/String 9",std::to_string(rF->GetMotorOutputPercent()));
	/*if (turning){
		output = 0;
	}*/
	rF->PIDWrite(output-modifier);
	rB->PIDWrite(output-modifier);
	lF->PIDWrite(output+modifier);
	lB->PIDWrite(output+modifier);
}
bool Drivetrain::AtSetpoint(){

	return (GetPosition()-GetSetpoint() < 3000 &&GetPosition()-GetSetpoint() > -3000) && (RobotMap::drivetrainLB->GetSensorCollection().GetQuadratureVelocity()<7&&RobotMap::drivetrainLB->GetSensorCollection().GetQuadratureVelocity()>-7);
}

void Drivetrain::SetBrakeMode(bool brake){
	if (brake){

		rB->SetNeutralMode(ctre::phoenix::motorcontrol::Brake);
		lB->SetNeutralMode(ctre::phoenix::motorcontrol::Brake);
		lF->SetNeutralMode(ctre::phoenix::motorcontrol::Brake);
		rF->SetNeutralMode(ctre::phoenix::motorcontrol::Brake);
	}
	else{

		rB->SetNeutralMode(ctre::phoenix::motorcontrol::Coast);
		lB->SetNeutralMode(ctre::phoenix::motorcontrol::Coast);
		lF->SetNeutralMode(ctre::phoenix::motorcontrol::Coast);
		rF->SetNeutralMode(ctre::phoenix::motorcontrol::Coast);
	}
}
void Drivetrain::Strafe(double rotations){
	double metToTicks = 10909.09/2;

	double degrees=metToTicks*metToTicks;
	Robot::gyroSubsystem->setDegrees(Robot::gyroSubsystem->gAngle());
	SetSetpoint(degrees);

	//Enable();

	rFmodifier += -0.3*(rotations / abs(rotations))	;
	rBmodifier += 0.3*(rotations / abs(rotations));
	lFmodifier += 0.3*(rotations / abs(rotations));
	lBmodifier += -0.3*(rotations / abs(rotations));
}
// Put methods for controlling this subsystem
// here. Call these from Commands.

