// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Encoder.h>
#include <frc/Doublesolenoid.h>
#include "rev/CANSparkMax.h"
#include <lib/NRollingAverage.h>
#include <lib/rate_limiter.h>
#include "Constants.h"
#include "lib/RblUtils.h"
#include "lib/utils.h"
#include <lib/Dynamic.h>
#include <math.h>

class Drivetrain : public frc2::SubsystemBase
{
public:
  Drivetrain();
  void Set(double speed);
  void SetVoltage(double right, double left);
  void ActiveBallShifterV1();
  void ActiveBallShifterV2();
  void ChangeBallShifter();
  void Drive(double joystick_V, double joystick_W);
  void DriveAuto(double speed, double rotation);
  double Calcul_De_Notre_Brave_JM(double forward, double turn, bool wheelSide); // Si wheelSide 0: roue droite / Si wheelSide 1: roue gauche
  bool isUpshiftingAllowed();
  bool isKickdownShiftingAllowed(); // ok
  void ShiftGearUp();
  void ShiftGearDown();

  Dynamic m_GearboxLeftOutRawRpt;                    // Vitesse instantanée de sortie de boite ( mesurée par le TroughBore Encoder )
  NdoubleRollingAverage m_GearboxLeftOutAveragedRpt; // Vitesse moyenne de sortie de boite (Moyenne glissante)
  double m_GearboxLeftOutAdjustedRpm;                // Vitesse de la gearbox gauche en RPM ( combinaison linéaire de la vitesse moyenne de sortie de boite et de la vitesse moyenne du supermoteur en entrée de boite)

  // Côté droit
  Dynamic m_GearboxRightOutRawRpt;                    // Vitesse instantanée de sortie de boite ( mesurée par le TroughBore Encoder )
  NdoubleRollingAverage m_GearboxRightOutAveragedRpt; // Vitesse moyenne de sortie de boite (Moyenne glissante)
  double m_GearboxRightOutAdjustedRpm;                // Vitesse de la gearbox droite en RPM ( combinaison linéaire de la vitesse moyenne de sortie de boite et de la vitesse moyenne du supermoteur en entrée de boite)

  Dynamic m_GearboxesOutAdjustedRpm; // Vitesse (translation) du robot exprimée en RPM

  double m_GearShiftingTimeLock; // Temps de blocage du changement de vitesse
  double m_CurrentGearboxRatio;  // Rapport (Reduction) de la vitesse engagée dans la  boite (V1 ou V2)

  Dynamic m_JoystickRaw_V;
  RateLimiter m_JoystickPrelimited_V; // joystick V rate limiter 1
  RateLimiter m_JoystickLimited_V;    // joystick V rate limiter 2

  Dynamic m_JoystickRaw_W;
  RateLimiter m_JoystickPrelimited_W; // joystick W rate limiter 1
  RateLimiter m_JoystickLimited_W;    // joystick W rate limiter 2

  enum class State
  {
    lowGear,
    highGear
  };

  State m_State;

  double m_sigma;

  frc::Encoder m_EncoderLeft{ID_ENCODER_DRIVE_TRAIN_LEFT_A, ID_ENCODER_DRIVE_TRAIN_LEFT_B, false, frc::Encoder::k4X};
  frc::Encoder m_EncoderRight{ID_ENCODER_DRIVE_TRAIN_RIGHT_A, ID_ENCODER_DRIVE_TRAIN_RIGHT_B, true, frc::Encoder::k4X};

private:
  rev::CANSparkMax m_MotorRight1{ID_MOTOR_DRIVE_TRAIN_RIGHT, rev::CANSparkLowLevel::MotorType::kBrushless};
  rev::CANSparkMax m_MotorRight2{ID_MOTOR_DRIVE_TRAIN_RIGHT_2, rev::CANSparkLowLevel::MotorType::kBrushless};
  rev::CANSparkMax m_MotorLeft1{ID_MOTOR_DRIVE_TRAIN_LEFT, rev::CANSparkLowLevel::MotorType::kBrushless};
  rev::CANSparkMax m_MotorLeft2{ID_MOTOR_DRIVE_TRAIN_LEFT_2, rev::CANSparkLowLevel::MotorType::kBrushless};

  frc::DoubleSolenoid m_BallShifterSolenoid{frc::PneumaticsModuleType::CTREPCM, ID_SOLENOID_SHIFTER_A, ID_SOLENOID_SHIFTER_B};
};
