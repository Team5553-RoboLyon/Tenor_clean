// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>
#include "subsystem/Intake.h"
#include "subsystem/Feeder.h"
#include "subsystem/Shooter.h"
#include "subsystem/Planetary.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending Command
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class Source
    : public frc2::CommandHelper<frc2::Command, Source>
{
public:
  Source(Shooter *pShooter, Feeder *pFeeder, Intake *pIntake, Planetary *pPlanetary);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  enum class State
  {
    Take,
    IsDetected,
    Detected,
    Catch,
    Recul,
    Loaded,
    End
  };
  State m_state;

  int m_count;
  Shooter *m_pShooter;
  Feeder *m_pFeeder;
  Intake *m_pIntake;
  Planetary *m_pPlanetary;
};
