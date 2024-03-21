// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix/motorcontrol/can/TalonFX.h>
#include "Constants.h"

class Intake : public frc2::SubsystemBase
{
public:
  Intake();
  void SetIntake(double speed);

private:
  ctre::phoenix::motorcontrol::can::TalonFX m_intakeMotorRight{ID_MOTOR_INTAKE};
};
