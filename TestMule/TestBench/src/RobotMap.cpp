#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"

std::shared_ptr<WPI_TalonSRX> RobotMap::FLDrive;
std::shared_ptr<WPI_TalonSRX> RobotMap::FRDrive;
std::shared_ptr<WPI_TalonSRX> RobotMap::BLDrive;
std::shared_ptr<WPI_TalonSRX> RobotMap::BRDrive;


void RobotMap::init() {

    frc::LiveWindow *lw = frc::LiveWindow::GetInstance();

    FLDrive.reset(new WPI_TalonSRX(0));
    FRDrive.reset(new WPI_TalonSRX(7));
    BLDrive.reset(new WPI_TalonSRX(2));
    BRDrive.reset(new WPI_TalonSRX(3));
    BRDrive->SetInverted(true);

}
