// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Spit.h"

Spit::Spit(Feeder *pFeeder, Intake *pIntake) : m_pFeeder(pFeeder), m_pIntake(pIntake)
{
  AddRequirements({m_pFeeder, m_pIntake});
}

// Called when the command is initially scheduled.
void Spit::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void Spit::Execute()
{
  m_pFeeder->SetFeeder(SPIT_FEEDER_SPEED);
  m_pIntake->SetIntake(SPIT_INTAKE_SPEED);
}

// Called once the command ends or is interrupted.
void Spit::End(bool interrupted)
{
  m_pFeeder->SetFeeder(STOP_FEEDER_SPEED);
  m_pIntake->SetIntake(STOP_INTAKE_SPEED);
}

// Returns true when the command should end.
bool Spit::IsFinished()
{
  if (m_count > 25)
  {
    return true;
  }
  else
  {
    m_count++;
    return false;
  }
}
