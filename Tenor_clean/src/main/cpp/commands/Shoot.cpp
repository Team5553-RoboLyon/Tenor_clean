#include "commands/Shoot.h"

Shoot::Shoot(Shooter *pShooter, Feeder *pFeeder, Planetary *pPlanetary, Camera *pCamera) : m_pShooter(pShooter), m_pFeeder(pFeeder), m_pPlanetary(pPlanetary), m_pCamera(pCamera)
{
  AddRequirements({m_pShooter, m_pFeeder, m_pPlanetary, m_pCamera});
}

void Shoot::Initialize()
{
  m_count = 0;
  m_state = State::Loaded;
}

void Shoot::Execute()
{
  shooter_speed = m_pShooter->shooterDataTable[m_pShooter->getNearestElementId(m_pCamera->GetPitch(ID_APRILTAG_MIDDLE, ID_APRILTAG_LEFT))][2];
  planteray_angle = m_pShooter->shooterDataTable[m_pShooter->getNearestElementId(m_pCamera->GetPitch(ID_APRILTAG_MIDDLE, ID_APRILTAG_LEFT))][1];
  // planteray_angle = 21.9 + 0.913 * m_pCamera->GetAngle() - 0.00817 * pow(m_pCamera->GetAngle(), 2.0);
  m_pPlanetary->SetSetpoint(planteray_angle);
  m_goal = shooter_speed * SHOOTER_GOALS_CONVERSION;
  // std::cout << shooter_speed << std::endl;
  // std::cout << planteray_angle << std::endl;
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
    m_pShooter->SetShooter(shooter_speed);
    if (NABS(m_pShooter->GetShooterVelocity()) > m_goal && m_pPlanetary->m_planetaryPid.AtSetpoint())
    {
      m_state = State::Shoot;
    }
    break;
  case State::Shoot:
    m_pFeeder->SetFeeder(CATCH_FEEDER_SPEED);
    m_pShooter->SetShooter(shooter_speed);
    if (!m_pFeeder->GetFeederInfraSensorValue())
    {
      m_state = State::Shooting;
      m_count = 0;
    }
    break;
  case State::Shooting:
    m_pFeeder->SetFeeder(CATCH_FEEDER_SPEED);
    m_pShooter->SetShooter(shooter_speed);
    if (m_pFeeder->GetFeederInfraSensorValue() && m_count > SHOOTER_COUNT_READY)
    {
      m_state = State::End;
    }
    break;
  case State::End:
    m_pFeeder->IsNoteLoaded = false;
    m_pPlanetary->SetSetpoint(REST_ANGLE);
    m_pFeeder->SetFeeder(STOP_FEEDER_SPEED);
    m_pShooter->SetShooter(STOP_SHOOTER_SPEED);
    m_pFeeder->IsRumbling = true;
    break;

  default:
    break;
  }
}
void Shoot::End(bool interrupted)
{
  m_pPlanetary->SetSetpoint(REST_ANGLE);
  m_pFeeder->SetFeeder(STOP_FEEDER_SPEED);
  m_pShooter->SetShooter(STOP_SHOOTER_SPEED);
}

bool Shoot::IsFinished()
{
  return false;
}
