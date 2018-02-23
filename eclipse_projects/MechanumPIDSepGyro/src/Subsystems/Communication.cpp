
#include "Communication.h"

#include "ctre/Phoenix.h"

#include "../Robot.h"
#include "../RobotMap.h"
using namespace std;
Communication::Communication() : frc::PIDSubsystem("test",0.00055,0,0.0007)  {//PID values
	SetAbsoluteTolerance(0.01);
	GetPIDController()->SetContinuous(false);
	SetOutputRange(-0.4,0.4);//Min and Max speed for the wheels
	SetSetpoint(0);


	if((sock = socket(AF_INET, SOCK_DGRAM , 0)) < 0)
	{
		perror("cannot create socket \n");
	}

	memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(PORT);
	if(bind(sock, reinterpret_cast<struct sockaddr *>(&myaddr), sizeof(myaddr)) < 0)
	{
		perror("bind failed");
	}
	setbuf(stdout, NULL);
}

void Communication::InitDefaultCommand() {
    // SetDefaultCommand(new MySpecialCommand());

}

void Communication::Periodic() {
    // Put code here to be run every loop
	recvlen = recvfrom(sock,buf,BUFSIZE, MSG_DONTWAIT, reinterpret_cast<struct sockaddr*>(&remaddr),&addrlen);
		if(recvlen >0)
		{


		}

		s = "";

		for(int i =0; i<recvlen; i++)
		{
			s.push_back(buf[i]);
		}
		if(s!=""){

			SmartDashboard::PutString("DB/String 7", s);
			xValue = 641;
			stringstream conversion(s);
			conversion >> xValue;
			xValue-=320;
		}


		//SmartDashboard::PutString("DB/String 5", std::to_string(xValue));
}



int Communication::getXvalue()
{
	/*xValue = 641;
	stringstream conversion(s);
	conversion >> xValue;
	return xValue-320;*/
	return 0;
}

double Communication::ReturnPIDInput(){
		pidInput = xValue;

	//SmartDashboard::PutString("DB/String 7", std::to_string(pidInput));
	return pidInput;
}
void Communication::UsePIDOutput(double output){
		modifier = output; //sets internal value to the PID output... Later called
		if(xValue ==321){
			modifier = 0;
		}


}
double Communication::GetModifier(){
	return modifier;
}

bool Communication::AtSetpoint()
{
	return (GetPosition()-GetSetpoint() < 30 &&GetPosition()-GetSetpoint() > -30)&&(RobotMap::drivetrainLB->GetSensorCollection().GetQuadratureVelocity()<2&&RobotMap::drivetrainLB->GetSensorCollection().GetQuadratureVelocity()>-2);
}
