#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
std::shared_ptr<Compressor> RobotMap::TestComp;
std::shared_ptr<DoubleSolenoid> RobotMap::TestSolenoid;
std::shared_ptr<WPI_TalonSRX> RobotMap::FRDrive;
std::shared_ptr<WPI_TalonSRX> RobotMap::FLDrive;
std::shared_ptr<WPI_TalonSRX> RobotMap::BLDrive;
std::shared_ptr<WPI_TalonSRX> RobotMap::BRDrive;
std::shared_ptr<AHRS> RobotMap::IMU;


void RobotMap::init() {

    frc::LiveWindow *lw = frc::LiveWindow::GetInstance();
    TestComp.reset(new Compressor(0));
    TestSolenoid.reset(new DoubleSolenoid(0,1));
    FRDrive.reset(new WPI_TalonSRX(7));
    BLDrive.reset(new WPI_TalonSRX(2));
    BRDrive.reset(new WPI_TalonSRX(3));
    FLDrive.reset(new WPI_TalonSRX(0));
    BRDrive->SetInverted(true);
    IMU.reset(new AHRS(SPI::Port::kMXP));

}
