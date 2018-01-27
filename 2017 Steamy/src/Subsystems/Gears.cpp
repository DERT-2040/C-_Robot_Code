#include "Gears.h"
#include "../RobotMap.h"
#include <string>
#include <iostream>

using namespace std;

Gears::Gears() : Subsystem("ExampleSubsystem") {

}


void Gears::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	timer.Stop();
	timer.Reset();

	talon.SetSafetyEnabled(false);
}


void Gears::AutoAction(bool inStart, bool inStop){


/*
	if (inStart)
		status = true;
	if (inStop)
		status = false;

	if (status){
		if (endNC -> Get()){
			triggerHit = true;
		}

		if (endNO -> Get() == endNC -> Get() || startNC -> Get() == startNO -> Get()){ //Trigger if something is wrong with the limits
			spark -> Set(0);
			SmartDashboard::PutString("DB/String 7", "Error in gear deployment");
		}else if (!triggerHit){
			spark -> Set(-1);
			SmartDashboard::PutString("DB/String 7", "Opening");
		}else{
			if(startNO -> Get() && !startNC -> Get() && timer.Get() > 7.0){
				spark -> Set(1);
				SmartDashboard::PutString("DB/String 7", "Closing");
			}else if (timer.Get() < 8.0){ //Some room for overlap, waits for 7 secs, then closes, then finishes
				if (timer.Get() == 0){ //Starts the timer
					timer.Start();
				}
				spark -> Set(0);
				SmartDashboard::PutString("DB/String 7", "Waiting");
			}else{
				spark -> Set(0);
				SmartDashboard::PutString("DB/String 7", "GearDeployed");
			}

		}
	}else{
		//spark -> Set(0);
		triggerHit = false;
		timer.Stop();
		timer.Reset();
	}
	*/
}



bool Gears::AutoGears(){


	double offset = 1;
		if (talon.Get() == 0){
		errorX = gearTarget -> GetErrorX();
		area = gearTarget -> GetArea();
		status = gearTarget -> GetStatus();
		}

		if (errorX<-10){
			offset*=-1;
		}

		if (status && !visionIn){
			if (errorX < -14 || errorX > -4){
				offset*=0.16;
				gearDrive -> PulseRotate(offset);
			} else if (errorX >-14 && errorX <-4 && area < 12000){
				gearDrive -> DriveStraight(.15);
			} /*else if (errorX >-7 || errorX <-18){
				errorX = abs(errorX);
				errorX /= 100;
				offset *= errorX * 0.35 +0.135;
				gearDrive -> Rotate(offset);
			}*/else{
				gearDrive -> Rotate(-.15);

			}

		}

			if(area > 12000 && !visionIn) //When vision is close enough, start gear deployment
				visionIn = true;

			if(visionIn){

				//autoGears = true;
				//SmartDashboard::PutString("DB/String 7", "GearDeployment");

				if(timer.Get() == 0)
					timer.Start();
				if (timer.Get() < 1.0){
					gearDrive -> DriveStraight(.22);
				}else if (timer.Get() < 2.3){
					gearDrive -> DriveStraight(.11); //Move forward gently
					talon.Set(0.9);
				}else if (timer.Get() < 3.6){
					gearDrive -> DriveStraight(-.2);
					talon.Set(0);
				}else{
					gearDrive -> Stop();
					talon.Set(0);
					autoGears = true;
				}

			}
			return autoGears;
		}

bool Gears::AutoVision(){


	double offset = 1;
		if (talon.Get() == 0){
		errorX = gearTarget -> GetErrorX();
		area = gearTarget -> GetArea();
		status = gearTarget -> GetStatus();
		}

		if (errorX<-10){
			offset*=-1;
		}

		if (status){
			if (errorX < -14 || errorX > -4){
				offset*=0.16;
				gearDrive -> Rotate(offset);
			} else if (errorX >-14 && errorX <-4 && area < 12000){
				gearDrive -> DriveStraight(.15);
			} /*else if (errorX >-7 || errorX <-18){
				errorX = abs(errorX);
				errorX /= 100;
				offset *= errorX * 0.35 +0.135;
				gearDrive -> Rotate(offset);
			}*/else{
				gearDrive -> Stop();
				gearDrive -> ResetEncoders();
				autoGears = true;
			}

		}
		return autoGears;
}

bool Gears::GearDeploy(){
	if(timer.Get() == 0)
		timer.Start();

	if (timer.Get() < 1.4){
		gearDrive -> DriveStraight(.1);
		talon.Set(.9);
	}else if (timer.Get() < 2.4){
		gearDrive -> DriveStraight(-.35);
		talon.Set(0);
	}else{
		gearDrive -> Stop();
		talon.Set(0);
		autoGears = true;
	}
	return autoGears;
}


void Gears::TeleopGears(bool input, bool output){
	if (input)
		status = 1;
	if (output)
		status = -1;

	if (status == 1){
		if (endNO -> Get() && !endNC -> Get()){
			talon.Set(1);
		}else{
			talon.Set(0);
		}
	}else if (status == -1){
		if(startNO -> Get() && !startNC -> Get()){
			talon.Set(-1);
		}else{
			talon.Set(0);
		}
	}
}

void Gears::Reset(){
	triggerHit = false;
	state = 0;
	autoGears = false;
	timer.Stop();
	timer.Reset();
}

void Gears::ManualReverse(bool emergency){
	if (emergency)
		talon.Set(.5);
	else
		talon.Set(0);
}

void Gears::Openplease(){
	//SmartDashboard::PutString("DB/String 7", "GearDeployment");

		if(timer.Get() == 0)
			timer.Start();
		if (timer.Get() < .6){
			gearDrive -> DriveStraight(.22);
		}else if (timer.Get() < 1.4){
			talon.Set(-0.60);
			gearDrive -> DriveStraight(.22); //Move forward gently
		}else if (timer.Get() < 2.2){
			gearDrive -> DriveStraight(-.25);
		}else{
			gearDrive -> Stop();
			talon.Set(0);
			autoGears = true;
		}

		int try1 = endNO -> Get();
		int try2 = endNC -> Get();
		int try3 = startNO -> Get();
		int try4 = startNC -> Get();
		SmartDashboard::PutString("DB/String 5", std::to_string(try1));
		SmartDashboard::PutString("DB/String 6", std::to_string(try2));
		SmartDashboard::PutString("DB/String 7", std::to_string(try3));
		SmartDashboard::PutString("DB/String 8", std::to_string(try4));

}

