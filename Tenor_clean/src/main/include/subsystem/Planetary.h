// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "rev/CANSparkMax.h"
#include "frc/Encoder.h"
#include "lib/Pid.h"
#include "Constants.h"
class Planetary : public frc2::SubsystemBase
{
public:
  Planetary();
  void SetPlanetary(double speed);
  void SetSetpoint(double setpoint);
  double GetEncoder();
  void Periodic();

  Pid m_planetaryPid{0.0, PLANETARY_PID_P, PLANETARY_PID_I, PLANETARY_PID_D};

private:
  rev::CANSparkMax m_planetaryMotor{ID_MOTOR_PLANETARY, rev::CANSparkMax::MotorType::kBrushless};
  frc::Encoder m_planetaryEncoder{ID_ENCODER_PLANETARY_A, ID_ENCODER_PLANETARY_B};
};
