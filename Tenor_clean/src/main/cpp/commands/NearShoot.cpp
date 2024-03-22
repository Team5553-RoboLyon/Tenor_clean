// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/NearShoot.h"

NearShoot::NearShoot(Shooter *pShooter, Planetary *pPlanetary, Feeder *pFeeder)
    : m_pShooter(pShooter), m_pPlanetary(pPlanetary), m_pFeeder(pFeeder)
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({pShooter, pPlanetary, pFeeder});
}

// Called when the command is initially scheduled.
void NearShoot::Initialize()
{
  m_count = 0;
  m_state = State::Loaded;
}

// Called repeatedly when this Command is scheduled to run
void NearShoot::Execute()
{
  m_pPlanetary->SetSetpoint(NEAR_ANGLE);
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
    m_pShooter->SetShooter(NEAR_SPEED_SHOOT); // 0.5
    if (NABS(m_pShooter->GetShooterVelocity()) > m_goal && m_pPlanetary->m_planetaryPid.AtSetpoint())
    {
      m_state = State::Shoot;
    }
    break;
  case State::Shoot:
    m_pFeeder->SetFeeder(CATCH_FEEDER_SPEED);
    m_pShooter->SetShooter(NEAR_SPEED_SHOOT); // 0.5
    if (!m_pFeeder->GetFeederInfraSensorValue())
    {
      m_state = State::Shooting;
      m_count = 0;
    }
    break;
  case State::Shooting:
    m_pFeeder->SetFeeder(CATCH_FEEDER_SPEED);
    m_pShooter->SetShooter(NEAR_SPEED_SHOOT);
    if (m_pFeeder->GetFeederInfraSensorValue() && m_count > SHOOTER_COUNT_READY)
    {
      m_state = State::End;
    }
    break;
  case State::End:
    m_pFeeder->IsNoteLoaded = false;
    m_pPlanetary->SetSetpoint(0.0);
    m_pFeeder->SetFeeder(STOP_FEEDER_SPEED);
    m_pShooter->SetShooter(STOP_SHOOTER_SPEED);
    m_pFeeder->IsRumbling = true;
    break;

  default:
    break;
  }
}

// Called once the command ends or is interrupted.
void NearShoot::End(bool interrupted)
{
  m_pFeeder->SetFeeder(STOP_FEEDER_SPEED);
  m_pShooter->SetShooter(STOP_SHOOTER_SPEED);
  m_pPlanetary->SetSetpoint(REST_ANGLE);
}

// Returns true when the command should end.
bool NearShoot::IsFinished()
{
  return false;
}
