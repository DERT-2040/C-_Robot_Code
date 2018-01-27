#include "Targeting.h"
#include "../RobotMap.h"

Targeting::Targeting() : Subsystem("ExampleSubsystem") {

}

void Targeting::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void Targeting::GetValues() {
	cX = m_table -> GetNumber("cX",cX);
	cY = m_table -> GetNumber("cY",cY);
	tgtStatus = m_table -> GetBoolean("tgtStatus", tgtStatus);
	tgtDist = m_table -> GetNumber("tgtDist", tgtDist);
	errorX = m_table -> GetNumber("errorX",errorX);
	errorY = m_table -> GetNumber("errorY",errorY);
	tgtAng = m_table -> GetNumber("tgtAng",tgtAng);
	position = m_table -> GetNumber("position",position);
	area = m_table -> GetNumber("area",area);
}

void Targeting::SendToDashboard() {
	GetValues();
	SmartDashboard::PutNumber("cX",(cX));
	SmartDashboard::PutNumber("cY",(cY));
	SmartDashboard::PutBoolean("tgtStatus",(tgtStatus));
	SmartDashboard::PutNumber("tgtDist",(tgtDist));
	SmartDashboard::PutNumber("errorX",(errorX));
	SmartDashboard::PutNumber("errorY",(errorY));
	SmartDashboard::PutNumber("tgtAng",(tgtAng));
}

bool Targeting::GetStatus(){
	return m_table -> GetBoolean("tgtStatus", tgtStatus);
}

double Targeting::GetCenter(){
	return m_table -> GetNumber("cX",cX/* FILLER TEXT */ );
}

double Targeting::GetDirection(){
	return m_table -> GetNumber("cX", cX /* FILLER TEXT*/ );
}

double Targeting::GetDistance(){
	return m_table -> GetNumber("tgtDist", tgtDist);
}

double Targeting::GetAngle(){
	return m_table -> GetNumber("tgtDist", tgtDist);
}

double Targeting::GetErrorX(){
	return m_table -> GetNumber("errorX", errorX);
}

int Targeting::GetArea(){
	return m_table -> GetNumber("area", area);
}

