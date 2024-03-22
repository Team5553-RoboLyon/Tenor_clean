// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>
#include "subsystem/Shooter.h"
#include "subsystem/Planetary.h"
#include "subsystem/Camera.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending Command
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class PreShoot
    : public frc2::CommandHelper<frc2::Command, PreShoot>
{
public:
  PreShoot(Shooter *pShooter, Planetary *pPlanetary, Camera *pCamera);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  double shooter_speed;
  double planteray_angle;

  Shooter *m_pShooter;
  Planetary *m_pPlanetary;
  Camera *m_pCamera;
};
