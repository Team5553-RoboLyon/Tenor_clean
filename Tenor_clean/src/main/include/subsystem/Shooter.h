// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix/motorcontrol/can/TalonFX.h>
#include "Constants.h"
#include "lib/RblUtils.h"

class Shooter : public frc2::SubsystemBase
{
public:
  Shooter();
  void SetShooter(double speed);
  void SetAmpShooter(double speed);
  double GetShooterVelocity();

  int getNearestElementId(double target);
  static constexpr double shooterDataTable[SHOOTER_TABLE_SIZE][3] = {
      // pitch, angle, vitesse
      {-10.6, 11, 0.95},
      {-9.66, 12.5, 0.9},
      {-9.1, 13, 0.9},
      {-8.43, 14, 0.85},
      {-7, 15, 0.85},
      {-5.75, 17, 0.85},
      {-4, 18, 0.8},
      {-2.8, 19, 0.73},
      {-1.54, 20, 0.7},
      {0.77, 23, 0.62},
      {3.11, 25, 0.6},
      {6.09, 27, 0.55},
      {9.77, 30.0, 0.5},
      {13.5, 33.0, 0.5},
      {17, 35.0, 0.5}

  };

private:
  ctre::phoenix::motorcontrol::can::TalonFX m_shooterMotorRight{ID_MOTOR_SHOOTER_DOWN};
  ctre::phoenix::motorcontrol::can::TalonFX m_shooterMotorLeft{ID_MOTOR_SHOOTER_HIGH};
};
