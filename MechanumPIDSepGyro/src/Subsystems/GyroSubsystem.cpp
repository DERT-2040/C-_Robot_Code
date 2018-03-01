
#include "GyroSubsystem.h"

#include "ctre/Phoenix.h"

#include "../Robot.h"
#include "../RobotMap.h"

GyroSubsystem::GyroSubsystem() : frc::PIDSubsystem("test",0.015,0,0.0175)  {//PID values
	SetAbsoluteTolerance(0.01);
	GetPIDController()->SetContinuous(false);
	SetOutputRange(-0.4,0.4);//Min and Max speed for the wheels
	RobotMap::sensorsAnalogGyro1->Reset();//Resets the Gyro to 0
}

void GyroSubsystem::InitDefaultCommand() {
    // SetDefaultCommand(new MySpecialCommand());
}

void GyroSubsystem::Periodic() {
    // Put code here to be run every loop
}
double GyroSubsystem::gAngle(){
	double angle = RobotMap::sensorsAnalogGyro1->GetAngle();
	return angle;
}
double GyroSubsystem::getGyroRate(){
	double rate = RobotMap::sensorsAnalogGyro1->GetRate();
	return rate;
}

double GyroSubsystem::ReturnPIDInput(){
	return gAngle();
}
void GyroSubsystem::UsePIDOutput(double output){
		modifier = output; //sets internal value to the PID output... Later called

		SmartDashboard::PutString("DB/String 2",std::to_string(modifier));
		SmartDashboard::PutString("DB/String 0",std::to_string((GetPosition())));
		SmartDashboard::PutString("DB/String 1",std::to_string((GetSetpoint())));
}
bool GyroSubsystem::AtSetpoint(){
	return (GetPosition()-GetSetpoint() < 2 &&GetPosition()-GetSetpoint() > -2)&&(RobotMap::drivetrainLB->GetSensorCollection().GetQuadratureVelocity()<2&&RobotMap::drivetrainLB->GetSensorCollection().GetQuadratureVelocity()>-2);
}
double GyroSubsystem::GetModifier(){
	Enable();
	GetPIDController()->SetEnabled(true);//Enable the PID
	return modifier;
}
void GyroSubsystem::setDegrees(double degrees){
	SetSetpoint(degrees);
}
void GyroSubsystem::ResetGyro(){
	RobotMap::sensorsAnalogGyro1->Reset();
}
