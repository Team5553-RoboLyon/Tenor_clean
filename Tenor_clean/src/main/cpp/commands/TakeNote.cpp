#include "commands/TakeNote.h"

TakeNote::TakeNote(Feeder *pFeeder, Intake *pIntake, Planetary *pPlanetary) : m_pFeeder(pFeeder), m_pIntake(pIntake), m_pPlanetary(pPlanetary)
{
  AddRequirements({m_pFeeder, m_pIntake, m_pPlanetary});
}

void TakeNote::Initialize()
{
  m_pPlanetary->SetSetpoint(TAKE_ANGLE);
  m_state = State::Catch;
}

void TakeNote::Execute()
{
  switch (m_state)
  {
  case State::Catch:
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
    m_pFeeder->SetFeeder(STOP_FEEDER_SPEED);
    m_pFeeder->IsNoteLoaded = true;
    break;
  default:
    break;
  }
}

void TakeNote::End(bool interrupted)
{
  m_pFeeder->SetFeeder(STOP_FEEDER_SPEED);
  m_pIntake->SetIntake(STOP_INTAKE_SPEED);
  m_pPlanetary->SetSetpoint(REST_ANGLE);
}
bool TakeNote::IsFinished()
{
  return false;
}
