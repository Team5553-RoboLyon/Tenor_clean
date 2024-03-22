// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>
#include <frc/filter/MedianFilter.h>
#include "subsystem/Shooter.h"
#include "subsystem/Feeder.h"
#include "subsystem/Planetary.h"
#include "subsystem/Camera.h"

class Shoot
    : public frc2::CommandHelper<frc2::Command, Shoot>
{
public:
  Shoot(Shooter *pShooter, Feeder *pFeeder, Planetary *pPlanetary, Camera *pCamera);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  int m_count;
  double shooter_speed;
  double planteray_angle;
  double m_goal;

  enum class State
  {
    Loaded,
    PreShoot,
    Shoot,
    Shooting,
    End
  };

  State m_state;

  Shooter *m_pShooter;
  Feeder *m_pFeeder;
  Planetary *m_pPlanetary;
  Camera *m_pCamera;
};
