#ifndef Targeting_H
#define Targeting_H

#include <Commands/Subsystem.h>
#include <iostream>
#include <memory>
#include <string>
#include "WPILib.h"
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>


class Targeting : public Subsystem {
private:
	frc::LiveWindow* lw = LiveWindow::GetInstance();
	std::shared_ptr<NetworkTable> m_table = NetworkTable::GetTable("Vision");
	//double seconds = 0;

public:
	int cX = 0;
	int cY = 0;
	double defaultValue = -1;
	bool tgtStatus = 0;
	double tgtDist = 10;
	double errorX = 0;
	double errorY = 0;
	double tgtAng = 0;
	double position = 2;
	int area = 0;
	//double seconds =0;
	Targeting();
	void InitDefaultCommand();
	void GetValues();
	void PutToDashboard();
	void SendToDashboard();
	/**
	 * Returns true if the robot can see the target or false if it can't
	 */
	bool GetStatus();
	/**
	 * Returns true if the robot is centered on the target or false if its not
	 */
	double GetCenter();
	/**
	 * Returns 1 if the robot is left of the target or -1 if it's right of the target
	 */
	double GetDirection();
	double GetDistance();
	double GetAngle();
	double GetErrorX();
	int GetArea();
};

#endif  // Targeting_H
