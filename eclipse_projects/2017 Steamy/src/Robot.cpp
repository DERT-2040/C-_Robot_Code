#include <memory>
#include <RobotDrive.h>
#include "WPILib.h"

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <CameraServer.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include "Commands/ExampleCommand.h"
#include "CommandBase.h"
#include "Commands/Testing.h"
#include "Commands/CenterAuto.h"
#include "Commands/RightAuto.h"
#include "Commands/LeftAuto.h"
#include "Commands/VisionAuto.h"
#include "Commands/DudAuto.h"
#include "Commands/ShootLeft.h"
#include "Commands/ShootRight.h"
#include "Commands/CenterNoVision.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/Climber.h"
#include "Subsystems/Targeting.h"
#include "Subsystems/Gears.h"
#include <Joystick.h>


frc::Timer timer;

class Robot: public frc::IterativeRobot {
private:
	Joystick *leftStick = new Joystick {0};
	Joystick *rightStick = new Joystick {1};
	Joystick *gamepad = new Joystick {2};
	DriveTrain *drive = new DriveTrain();
	Shooter *shooter = new Shooter();
	Climber *climber = new Climber();
	Targeting *vision = new Targeting();
	Gears *gears = new Gears();
	int gamepadPOV;
public:
	void RobotInit() override {

		//chooser.AddDefault("Default Auto", new ExampleCommand());
		// chooser.AddObject("My Auto", new MyAutoCommand());
		//frc::SmartDashboard::PutData("Auto Modes", &chooser);
		CameraServer::GetInstance()-> StartAutomaticCapture();
	}

	/**
	 * This function is called once each time the robot enters Disabled mode.
	 * You can use it to reset any subsystem information you want to clear when
	 * the robot is disabled.
	 */
	void DisabledInit() override {

	}

	void DisabledPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	/**
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString code to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional commands to the
	 * chooser code above (like the commented example) or additional comparisons
	 * to the if-else structure below with additional strings & commands.
	 */
	void AutonomousInit() override {
		/* std::string autoSelected = frc::SmartDashboard::GetString("Auto Selector", "Default");
		if (autoSelected == "My Auto") {
			autonomousCommand.reset(new MyAutoCommand());
		}
		else {
			autonomousCommand.reset(new ExampleCommand());
		} */

		std::string autoSelected = frc::SmartDashboard::GetString("DB/String 0", "Default");
		if (autoSelected == "Center") {
			autonomousCommand = new CenterAuto();
		}else if (autoSelected == "Right"){
			autonomousCommand = new RightAuto();
		}else if (autoSelected == "Left"){
			autonomousCommand = new LeftAuto();
		}else if (autoSelected == "Vision"){
			autonomousCommand = new VisionAuto();
		}else if (autoSelected == "SLeft"){
			autonomousCommand = new ShootLeft();
		}else if (autoSelected == "SRight"){
			autonomousCommand = new ShootRight();
		}else if (autoSelected == "NVision"){
			autonomousCommand = new CenterNoVision();
		}else{
			autonomousCommand = new DudAuto();
		}
		if (autonomousCommand != nullptr)
			autonomousCommand->Start();
		else
			SmartDashboard::PutString("DB/String 0", "No Command");

		drive -> ResetEncoders();
	}

	void AutonomousPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (autonomousCommand != nullptr) {
			autonomousCommand->Cancel();
		}
		gears -> Reset();
	}

	void TeleopPeriodic() override {
		drive -> Teleop(leftStick -> GetX(), leftStick -> GetY(), rightStick -> GetX(), rightStick -> GetZ(), gamepad -> GetRawButton(1), gamepad -> GetPOV());
		shooter -> Shoot(gamepad -> GetRawButton(6), gamepad -> GetRawButton(5));
		climber -> Climb(gamepad -> GetRawButton(4));
		//vision -> SendToDashboard();
		gears -> TeleopGears(gamepad -> GetRawButton(3), gamepad -> GetRawButton(2));
		//gears -> ManualReverse(rightStick -> GetRawButton(10));
	}

	void TestPeriodic() override {
		frc::LiveWindow::GetInstance()->Run();
	}

private:
	//std::unique_ptr<frc::Command> autonomousCommand;
	frc::Command* autonomousCommand = nullptr;
	frc::SendableChooser<frc::Command*> chooser;
};

START_ROBOT_CLASS(Robot)
