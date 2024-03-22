// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystem/Drivetrain.h"

Drivetrain::Drivetrain() : m_GearboxLeftOutAveragedRpt(AVERAGE_SAMPLES_NUMBER),
                           m_GearboxRightOutAveragedRpt(AVERAGE_SAMPLES_NUMBER)

{
    m_MotorLeft1.RestoreFactoryDefaults(); // reset des paramètres du moteur
    m_MotorLeft2.RestoreFactoryDefaults();

    m_MotorRight1.RestoreFactoryDefaults();
    m_MotorRight2.RestoreFactoryDefaults();

    m_MotorLeft1.SetSmartCurrentLimit(DRIVETRAIN_CURRENT_LIMIT);
    m_MotorLeft2.SetSmartCurrentLimit(DRIVETRAIN_CURRENT_LIMIT);

    m_MotorRight1.SetSmartCurrentLimit(DRIVETRAIN_CURRENT_LIMIT);
    m_MotorRight2.SetSmartCurrentLimit(DRIVETRAIN_CURRENT_LIMIT);

    m_MotorLeft1.SetInverted(DRIVETRAIN_MOTOR_LEFT_INVERTED);
    m_MotorLeft2.SetInverted(DRIVETRAIN_MOTOR_LEFT_INVERTED);

    m_MotorRight1.SetInverted(DRIVETRAIN_MOTOR_RIGHT_INVERTED);
    m_MotorRight2.SetInverted(DRIVETRAIN_MOTOR_RIGHT_INVERTED);

    m_MotorLeft1.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_MotorLeft2.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    m_MotorRight1.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_MotorRight2.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    m_MotorLeft1.EnableVoltageCompensation(DRIVETRAIN_VOLTAGE_COMPENSATION);
    m_MotorLeft2.EnableVoltageCompensation(DRIVETRAIN_VOLTAGE_COMPENSATION);

    m_MotorRight1.EnableVoltageCompensation(DRIVETRAIN_VOLTAGE_COMPENSATION);
    m_MotorRight2.EnableVoltageCompensation(DRIVETRAIN_VOLTAGE_COMPENSATION);

    m_MotorLeft2.Follow(m_MotorLeft1);
    m_MotorRight2.Follow(m_MotorRight1);

    m_JoystickPrelimited_V.Reset(0.0, 0.0, 2.0); // reset des rate limiters
    m_JoystickLimited_V.Reset(0.0, 0.0, 0.05);   // 0.04

    m_JoystickPrelimited_W.Reset(0.0, 0.0, 2.0);
    m_JoystickLimited_W.Reset(0.0, 0.0, 0.05); // 0.0'

    m_EncoderLeft.SetDistancePerPulse(DRIVETRAIN_DISTANCE_PER_PULSE);
    m_EncoderRight.SetDistancePerPulse(DRIVETRAIN_DISTANCE_PER_PULSE);

    ActiveBallShifterV1();
    m_State = State::lowGear;
    m_CurrentGearboxRatio = REDUC_V1;
};

void Drivetrain::Set(double speed)
{
    m_MotorLeft1.Set(speed);
    m_MotorRight1.Set(speed);
}

void Drivetrain::SetVoltage(double right, double left)
{
    m_MotorLeft1.Set(left / 12.0);
    m_MotorRight1.Set(right / 12.0);
}

void Drivetrain::DriveAuto(double speed, double rotation)
{
    m_MotorLeft1.Set(speed + rotation);
    m_MotorRight1.Set(speed - rotation);
}

void Drivetrain::ActiveBallShifterV1()
{
    m_BallShifterSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
}

void Drivetrain::ActiveBallShifterV2()
{
    m_BallShifterSolenoid.Set(frc::DoubleSolenoid::Value::kReverse);
}

void Drivetrain::ChangeBallShifter()
{
    if (m_BallShifterSolenoid.Get() == frc::DoubleSolenoid::Value::kForward)
    {
        ActiveBallShifterV2();
    }
    else
    {
        ActiveBallShifterV1();
    }
}

double Drivetrain::Calcul_De_Notre_Brave_JM(double forward, double turn, bool wheelSide) // calcule la vitesse des roues
{
    double m_forward = forward;
    double m_turn = turn;

    double left_wheel = m_forward + m_turn * m_sigma;
    double right_wheel = m_forward - m_turn * m_sigma;

    double k;
    k = 1.0 / (NMAX(1, NMAX(NABS(left_wheel), NABS(right_wheel))));
    left_wheel *= k;
    right_wheel *= k;

    if (wheelSide == 0)
        return right_wheel;
    else
        return left_wheel;
}

bool Drivetrain::isUpshiftingAllowed()
{
    if (NABS(m_GearboxesOutAdjustedRpm.m_current) > UP_SHIFTING_POINT_GEARBOXES_OUT_RPM and
        NABS(m_JoystickRaw_V.m_current) > UP_SHIFTING_POINT_JOYSTICK_V)
        return true;
    else
        return false;
}

bool Drivetrain::isKickdownShiftingAllowed()
{
    if (NABS(m_GearboxesOutAdjustedRpm.m_current) < KICKDOWN_SHIFTING_POINT_GEARBOXES_OUT_RPM)
        return true;
    else
        return false;
}

void Drivetrain::ShiftGearUp()
{
    m_JoystickLimited_V.Update(m_JoystickPrelimited_V.m_current);
    ActiveBallShifterV2();
}

void Drivetrain::ShiftGearDown() // passage de la vitesse en V1
{
    m_JoystickLimited_V.Update(m_JoystickPrelimited_V.m_current);
    ActiveBallShifterV1();
}

void Drivetrain::Drive(double joystick_V, double joystick_W)
{
    m_GearboxRightOutRawRpt.set(m_EncoderRight.GetDistance());
    m_GearboxRightOutAveragedRpt.add(m_GearboxRightOutRawRpt.m_delta);
    m_GearboxLeftOutRawRpt.set(m_EncoderLeft.GetDistance());
    m_GearboxLeftOutAveragedRpt.add(m_GearboxLeftOutRawRpt.m_delta);

    m_GearboxRightOutAdjustedRpm = (m_GearboxRightOutAveragedRpt.get() * (60 / TICK_DT));
    m_GearboxLeftOutAdjustedRpm = (m_GearboxLeftOutAveragedRpt.get() * (60 / TICK_DT));

    m_GearboxesOutAdjustedRpm.set((m_GearboxRightOutAdjustedRpm + m_GearboxLeftOutAdjustedRpm) / 2.0);

    m_JoystickRaw_V.set(joystick_V);
    m_JoystickLimited_V.Update(m_JoystickPrelimited_V.Update(joystick_V));

    m_JoystickRaw_W.set(joystick_W);
    m_JoystickLimited_W.Update(m_JoystickPrelimited_W.Update(joystick_W));

    switch (m_State)
    {
    case State::lowGear:
    {
        m_sigma = NLERP(0.7, 0.5, NABS(joystick_V)); // 0401
        if (isUpshiftingAllowed())                   // and brakeButton == false
        {
            m_CurrentGearboxRatio = REDUC_V2;
            ShiftGearUp();
            m_State = State::highGear;
        }
    }
    break;

    case State::highGear:
    {
        m_sigma = NLERP(0.7, 0.5, NABS(joystick_V)); // 0401

        if (isKickdownShiftingAllowed()) // or brakeButton == true
        {
            m_CurrentGearboxRatio = REDUC_V1;
            ShiftGearDown();
            m_State = State::lowGear;
        }
    }
    break;
    default:
        break;
    }

    m_MotorLeft1.Set(Calcul_De_Notre_Brave_JM(m_JoystickLimited_V.m_current, std::sin(m_JoystickLimited_W.m_current * (NF64_PI / 2)), 0));
    m_MotorRight1.Set(Calcul_De_Notre_Brave_JM(m_JoystickLimited_V.m_current, std::sin(m_JoystickLimited_W.m_current * (NF64_PI / 2)), 1));
}
