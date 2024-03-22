// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/StageShoot.h"

StageShoot::StageShoot(Shooter *pShooter, Planetary *pPlanetary, Feeder *pFeeder)
    : m_pShooter(pShooter), m_pPlanetary(pPlanetary), m_pFeeder(pFeeder)
{
  AddRequirements({m_pShooter, m_pPlanetary, m_pFeeder});
}
// Called when the command is initially scheduled.
void StageShoot::Initialize()
{
  m_count = 0;
  m_state = State::Loaded;
}

// Called repeatedly when this Command is scheduled to run
void StageShoot::Execute()
{
  m_pPlanetary->SetSetpoint(STAGE_ANGLE);
  m_goal = NEAR_SPEED_SHOOT * SHOOTER_GOALS_CONVERSION;
  m_count++;
  switch (m_state)
  {
  case State::Loaded:
    m_pFeeder->SetFeeder(STOP_FEEDER_SPEED);
    if (m_pFeeder->IsNoteLoaded)
    {
      m_state = State::PreShoot;
    }
    break;
  case State::PreShoot:
    m_pShooter->SetShooter(STAGE_SPEED_SHOOT); // 0.5
    if (NABS(m_pShooter->GetShooterVelocity()) > m_goal && m_pPlanetary->m_planetaryPid.AtSetpoint())
    {
      m_state = State::Shoot;
    }
    break;
  case State::Shoot:
    m_pFeeder->SetFeeder(CATCH_FEEDER_SPEED);
    m_pShooter->SetShooter(STAGE_SPEED_SHOOT); // 0.5
    if (!m_pFeeder->GetFeederInfraSensorValue())
    {
      m_state = State::Shooting;
      m_count = 0;
    }
    break;
  case State::Shooting:
    m_pFeeder->SetFeeder(CATCH_FEEDER_SPEED);
    m_pShooter->SetShooter(STAGE_SPEED_SHOOT);
    if (m_pFeeder->GetFeederInfraSensorValue() && m_count > SHOOTER_COUNT_READY)
    {
      m_state = State::End;
    }
    break;
  case State::End:
    m_pPlanetary->SetSetpoint(REST_ANGLE);
    m_pFeeder->SetFeeder(STOP_FEEDER_SPEED);
    m_pShooter->SetShooter(STOP_SHOOTER_SPEED);
    m_pFeeder->IsNoteLoaded = false;
    m_pFeeder->IsRumbling = true;
    break;

  default:
    break;
  }
}

// Called once the command ends or is interrupted.
void StageShoot::End(bool interrupted)
{
  m_pPlanetary->SetSetpoint(REST_ANGLE);
  m_pFeeder->SetFeeder(STOP_FEEDER_SPEED);
  m_pShooter->SetShooter(STOP_SHOOTER_SPEED);
}

// Returns true when the command should end.
bool StageShoot::IsFinished()
{
  return false;
}
