// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>
#include "subsystem/Intake.h"
#include "subsystem/Feeder.h"
#include "subsystem/Planetary.h"

class TakeNote
    : public frc2::CommandHelper<frc2::Command, TakeNote>
{
public:
  TakeNote(Feeder *pFeeder, Intake *pIntake, Planetary *pPlanetary);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  enum class State
  {
    Catch,
    Recul,
    Loaded,
    End
  };

  State m_state;

  Feeder *m_pFeeder;
  Intake *m_pIntake;
  Planetary *m_pPlanetary;
};
