// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <optional>

#include <frc/TimedRobot.h>
#include <frc2/command/CommandPtr.h>
#include "lib/NL/MotionControl/DriveTrain/Characterization/NLMotorCharacterization.h"
#include "lib/NL/MotionControl/Trajectory/NLFollowerTank.h"
#include "lib/NL/MotionControl/Trajectory/NLTrajectoryPack.h"
#include "lib/NL/MotionControl/Trajectory/NLTrajectoryActionMessagesEnum.h"
#include "lib/NL/MotionControl/Trajectory/NLTrajectorySystemMessage.h"
#include <AHRS.h>

#include "RobotContainer.h"

class Robot : public frc::TimedRobot
{
public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void DisabledExit() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void AutonomousExit() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TeleopExit() override;
  void TestInit() override;
  void TestPeriodic() override;
  void TestExit() override;

  void TakeNoteSwitch();
  void ShootSwitch();
  void PreShoot();
  void NearShoot();
  void Shoot(double speed, double angle);

  void Center2Auto();
  enum class StateCenter2Auto
  {
    Nearshoot,
    Backward,
    wait,
    Shooting,
    End
  };
  StateCenter2Auto m_stateCenter2Auto;
  bool m_center2Auto;

  void ShootOnly();
  enum class StateShootOnly
  {
    Nearshoot,
    Backward,
    End
  };
  StateShootOnly m_stateShootOnly;
  bool m_shootOnly;

  enum class StateTakeNote
  {
    Catch,
    Recul,
    Loaded,
    End,
    nule
  };

  StateTakeNote m_stateTakeNote;
  bool m_takeNote;

  enum class StateShootSwitch
  {
    Loaded,
    PreShoot,
    Shoot,
    Shooting,
    End
  };

  StateShootSwitch m_stateShootSwitch;
  double m_goal;
  double shooter_speed;
  double planteray_angle;
  int m_count;
  bool m_shoot;
  int m_countCenter;
  int m_countOnly;
  int m_countable;

  bool m_preShoot;

  enum class StateNearShoot
  {
    PreShoot,
    Shoot,
    Shooting,
    End
  };

  StateNearShoot m_stateNearShoot;

  enum class StateShoot
  {
    Loaded,
    PreShoot,
    Shoot,
    Shooting,
    End
  };

  StateShoot m_stateShoot;

  RobotContainer m_robotContainer;
  NLMOTOR_CHARACTERIZATION m_CrtzL;
  NLMOTOR_CHARACTERIZATION m_CrtzR;

  NLTRAJECTORY_PACK m_TrajectoryPack;
  NLFOLLOWER_TANK m_follower;

  // AHRS m_gyro{frc::SerialPort::Port::kUSB};
  int m_state;
  double m_encoderRightValue;
  double m_encoderLeftValue;
  double m_gyroAngle;
  double m_VoltageLeft;
  double m_VoltageRight;
  double m_LeftV;
  double m_RightV;
};
