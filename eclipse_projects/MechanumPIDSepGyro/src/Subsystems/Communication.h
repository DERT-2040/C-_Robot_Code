// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future


#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sstream>
#include <iostream>
#include <string>
/**
 *
 *
 * @author ExampleAuthor
 */
class Communication: public frc::PIDSubsystem {
private:
	double ReturnPIDInput();//Internal Function Only!
	void UsePIDOutput(double output);//Internal Function Only!M

	int xValue =641;
public:
	Communication();
	void InitDefaultCommand() override;
		void Periodic() override;
		double pidInput = 0;
		double modifier = 0;
	#define PORT (5005u)
	#define BUFSIZE (1024u)
	struct sockaddr_in myaddr;
	struct sockaddr_in remaddr;
	socklen_t addrlen = sizeof(remaddr);
	int recvlen = 0;
	int sock;
	unsigned char buf[BUFSIZE];
	int getXvalue();
	double GetModifier();
	bool AtSetpoint();
	std::string s;
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
};

#endif
