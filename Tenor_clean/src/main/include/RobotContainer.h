// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc/Joystick.h>
#include <frc/XboxController.h>
#include <frc2/command/button/POVButton.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc/Compressor.h>

#include "subsystem/Drivetrain.h"
#include "subsystem/Camera.h"
#include "subsystem/Feeder.h"
#include "subsystem/Intake.h"
#include "subsystem/Planetary.h"
#include "subsystem/Shooter.h"

#include "commands/Drive.h"
#include "commands/PreShoot.h"
#include "commands/Shoot.h"
#include "commands/TakeNote.h"
#include "commands/NearShoot.h"
#include "commands/AmpShoot.h"
#include "commands/StageShoot.h"
#include "commands/Spit.h"

class RobotContainer
{
public:
  RobotContainer();
  void ConfigureBindings();

  frc::Joystick m_joystickRight{0};
  frc::Joystick m_joystickLeft{1};
  frc::XboxController m_xboxControllerCopilote{2};

  frc2::JoystickButton m_buttonPreShoot{&m_xboxControllerCopilote, 5};
  frc2::JoystickButton m_buttonShoot{&m_xboxControllerCopilote, 6};
  frc2::JoystickButton m_buttonNearShoot{&m_xboxControllerCopilote, 1};
  frc2::JoystickButton m_buttonAmpShoot{&m_xboxControllerCopilote, 4};
  frc2::JoystickButton m_buttonStageShoot{&m_xboxControllerCopilote, 2};

  frc2::POVButton m_buttonTakeNote{&m_xboxControllerCopilote, 0};

  frc::Compressor m_compressor{frc::PneumaticsModuleType::CTREPCM};

  Drivetrain m_drivetrain;
  Shooter m_shooter;
  Feeder m_feeder;
  Planetary m_planetary;
  Camera m_camera;
  Intake m_intake;
};
