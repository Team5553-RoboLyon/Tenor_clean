// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "photon/PhotonCamera.h"
#include "photon/PhotonUtils.h"
#include "lib/RblUtils.h"
#include "lib/Pid.h"
#include "Constants.h"
#include <wpi/SpanExtras.h>
#include "photon/targeting/PhotonTrackedTarget.h"
#include <vector>
#include "lib/NRollingAverage.h"

class Camera : public frc2::SubsystemBase
{
public:
  Camera();
  double GetPitch(int Id_1, int Id_2);
  void Periodic() override;

  photon::PhotonCamera m_camera{"IRcam"};

  NdoubleRollingAverage m_verticalRollingAverage{10};
};
