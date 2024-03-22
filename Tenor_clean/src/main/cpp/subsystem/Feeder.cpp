// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystem/Feeder.h"

Feeder::Feeder()
{
    m_feederMotor.ConfigFactoryDefault();
    m_feederMotor.SetInverted(FEEDER_MOTOR_INVERTED);
    m_feederMotor.EnableVoltageCompensation(true);
    m_feederMotor.ConfigVoltageCompSaturation(FEEDER_VOLTAGE_COMPENSATION);
    m_feederMotor.ConfigSupplyCurrentLimit(ctre::phoenix::motorcontrol::SupplyCurrentLimitConfiguration(true, FEEDER_CURRENT_LIMIT, FEEDER_CURRENT_LIMIT, 0));
    m_feederMotor.ConfigClosedloopRamp(FEEDER_RAMP);

    IsNoteLoaded = false;
};

void Feeder::SetFeeder(double speed)
{
    m_feederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}

bool Feeder::GetFeederInfraSensorValue()
{
    return m_feederInfraSensor.Get();
}
