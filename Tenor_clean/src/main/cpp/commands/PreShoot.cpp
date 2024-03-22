// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/PreShoot.h"

PreShoot::PreShoot(Shooter *pShooter, Planetary *pPlanetary, Camera *pCamera) : m_pShooter(pShooter), m_pPlanetary(pPlanetary), m_pCamera(pCamera)
{
  AddRequirements({m_pShooter, m_pPlanetary, m_pCamera});
}

// Called when the command is initially scheduled.
void PreShoot::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void PreShoot::Execute()
{
  shooter_speed = m_pShooter->shooterDataTable[m_pShooter->getNearestElementId(m_pCamera->GetPitch(ID_APRILTAG_MIDDLE, ID_APRILTAG_LEFT))][2];
  planteray_angle = m_pShooter->shooterDataTable[m_pShooter->getNearestElementId(m_pCamera->GetPitch(ID_APRILTAG_MIDDLE, ID_APRILTAG_LEFT))][1];

  m_pShooter->SetShooter(shooter_speed);
  m_pPlanetary->SetSetpoint(planteray_angle);
}

// Called once the command ends or is interrupted.
void PreShoot::End(bool interrupted)
{
  m_pShooter->SetShooter(STOP_SHOOTER_SPEED);
  m_pPlanetary->SetSetpoint(REST_ANGLE);
}

// Returns true when the command should end.
bool PreShoot::IsFinished()
{
  return false;
}
