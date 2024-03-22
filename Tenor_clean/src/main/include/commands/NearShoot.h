
#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>
#include "subsystem/Shooter.h"
#include "subsystem/Planetary.h"
#include "subsystem/Feeder.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending Command
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class NearShoot
    : public frc2::CommandHelper<frc2::Command, NearShoot>
{
public:
  NearShoot(Shooter *pShooter, Planetary *pPlanetary, Feeder *pFeeder);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  Shooter *m_pShooter;
  Planetary *m_pPlanetary;
  Feeder *m_pFeeder;

  int m_count;
  double shooter_speed;
  double planteray_angle;
  double m_goal;

  enum class State
  {
    Loaded,
    PreShoot,
    Shoot,
    Shooting,
    End
  };

  State m_state;
};
