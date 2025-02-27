// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Source.h"

Source::Source(Shooter *pShooter, Feeder *pFeeder, Intake *pIntake, Planetary *pPlanetary) : m_pShooter(pShooter), m_pFeeder(pFeeder), m_pIntake(pIntake), m_pPlanetary(pPlanetary)
{
  AddRequirements({m_pShooter, m_pFeeder, m_pIntake, m_pPlanetary});
}

// Called when the command is initially scheduled.
void Source::Initialize()
{
  m_pPlanetary->SetSetpoint(100.0);
  m_state = State::Take;
}

// Called repeatedly when this Command is scheduled to run
void Source::Execute()
{
  switch (m_state)
  {
  case State::Take:
    m_pFeeder->SetFeeder(-0.4);
    m_pShooter->SetShooter(-0.2);
    if (!m_pFeeder->GetFeederInfraSensorValue())
    {
      m_state = State::IsDetected;
    }
    break;
  case State::IsDetected:
    m_pFeeder->SetFeeder(-0.4);
    m_pShooter->SetShooter(-0.2);
    if (m_pFeeder->GetFeederInfraSensorValue())
    {
      m_state = State::Catch;
    }
    break;
  case State::Catch:
    m_pShooter->SetShooter(STOP_SHOOTER_SPEED);
    m_pFeeder->SetFeeder(CATCH_FEEDER_SPEED);
    m_pIntake->SetIntake(INTAKE_SPEED);
    if (!m_pFeeder->GetFeederInfraSensorValue())
    {
      m_pFeeder->IsRumbling = true;
      m_pIntake->SetIntake(STOP_INTAKE_SPEED);
      m_pFeeder->SetFeeder(SPIT_FEEDER_SPEED);
      m_state = State::Recul;
    }
    break;
  case State::Recul:
    m_pFeeder->SetFeeder(SPIT_FEEDER_SPEED);
    if (m_pFeeder->GetFeederInfraSensorValue())
    {
      m_pFeeder->SetFeeder(STOP_FEEDER_SPEED);
      m_state = State::Loaded;
    }
    break;
  case State::Loaded:
    m_pFeeder->IsRumbling = true;
    m_pFeeder->SetFeeder(STOP_FEEDER_SPEED);
    m_pFeeder->IsNoteLoaded = true;
  }
}

// Called once the command ends or is interrupted.
void Source::End(bool interrupted)
{
  m_pFeeder->SetFeeder(STOP_FEEDER_SPEED);
  m_pShooter->SetShooter(STOP_SHOOTER_SPEED);
  m_pPlanetary->SetSetpoint(REST_ANGLE);
}

// Returns true when the command should end.
bool Source::IsFinished()
{
  return false;
}
