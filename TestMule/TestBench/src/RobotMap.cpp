#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
/*
std::shared_ptr<Compressor> RobotMap::TestComp;
std::shared_ptr<DoubleSolenoid> RobotMap::TestSolenoid;
*/
std::shared_ptr<WPI_TalonSRX> RobotMap::FRDrive;
std::shared_ptr<WPI_TalonSRX> RobotMap::FLDrive;
std::shared_ptr<WPI_TalonSRX> RobotMap::BLDrive;
std::shared_ptr<WPI_TalonSRX> RobotMap::BRDrive;
std::shared_ptr<AHRS> RobotMap::IMU;


void RobotMap::init() {

    frc::LiveWindow *lw = frc::LiveWindow::GetInstance();
    FRDrive.reset(new WPI_TalonSRX(7));
    FRDrive->SetInverted(true);
    BLDrive.reset(new WPI_TalonSRX(2));
    BLDrive->SetInverted(true);

    BRDrive.reset(new WPI_TalonSRX(3));
    FLDrive.reset(new WPI_TalonSRX(0));
    FLDrive->SetInverted(true);
    IMU.reset(new AHRS(SPI::Port::kMXP));

}
