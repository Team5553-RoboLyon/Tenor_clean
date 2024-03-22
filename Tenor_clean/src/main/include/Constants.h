/////////////////////// DRIVING CONSTANTS ///////////////////////

#define MOTOR_WF_RPM 5874.0 // Free Speed théorique du moteur à la tension de reference (12V)
#define MOTOR_TS_NM 3.35    // Stall Torque théorique du moteur à la tension de reference (12V)

#define REDUC_V1 12.13
#define REDUC_V2 7.64

#define TURNING_TOLERANCE 0.05

#define UP_SHIFTING_POINT_JOYSTICK_V 0.8                                    // Valeur minimum du joystick V pour passer en vitesse 2
#define UP_SHIFTING_POINT_JOYSTICK_V_VARIATION 0.0                          // Valeur minimum de la variation (=delta) du joystick V pour passer en vitesse 2
#define UP_SHIFTING_POINT_GEARBOXES_OUT_RPM (MOTOR_WF_RPM * 0.5 / REDUC_V1) // Valeur minimum de la vitesse de sortie de boites pour passer en vitesse 2
#define UP_SHIFTING_POINT_GEARBOXES_OUT_RPM2 0.0                            // Valeur minimum de l'accel.  de sortie de boites pour passer en vitesse 2

#define KICKDOWN_SHIFTING_POINT_GEARBOXES_OUT_RPM (MOTOR_WF_RPM * 0.3 / REDUC_V2) // Valeur max "haute" de la vitesse de sortie de boites pour retrograder en vitesse 1
#define KICKDOWN_SHIFTING_POINT_JOYSTICK_V 0.6                                    // Valeur minimum du joystick V pour retrograder en vitesse 1 afin de re-accelerer fort
#define KICKDOWN_SHIFTING_POINT_JOYSTICK_V_VARIATION 0.2                          // Valeur minimum de la variation (=delta) du joystick V pour retrograder en vitesse 1

#define COASTDOWN_SHIFTING_POINT_GEARBOXES_OUT_RPM (MOTOR_WF_RPM * 0.05 / REDUC_V2) // Valeur max "basse" de la vitesse de sortie de boites pour retrograder en vitesse 1

#define GEARSHIFTING_TIMELOCK 0.26 // 0.08

#define TICK_DT 0.02             // durée d'un tick en seconde
#define AVERAGE_SAMPLES_NUMBER 5 // nombre de samples pour la moyenne

// #########################    ID Joystick    #########################

#define ID_JOYSTICK_RIGHT 0
#define ID_JOYSTICK_LEFT 1
#define ID_JOYSTICK_COPILOTER 2

// #########################    ID Motor    #########################

#define ID_MOTOR_DRIVE_TRAIN_RIGHT 1
#define ID_MOTOR_DRIVE_TRAIN_RIGHT_2 2
#define ID_MOTOR_DRIVE_TRAIN_LEFT 3
#define ID_MOTOR_DRIVE_TRAIN_LEFT_2 4

#define ID_MOTOR_INTAKE 5

#define ID_MOTOR_FEEDER 7

#define ID_MOTOR_SHOOTER_DOWN 8
#define ID_MOTOR_SHOOTER_HIGH 9

#define ID_MOTOR_PLANETARY 10

// #########################    ID Solenoid    #########################
#define ID_SOLENOID_SHIFTER_A 0
#define ID_SOLENOID_SHIFTER_B 1

// #########################    ID Encoder    #########################

#define ID_ENCODER_DRIVE_TRAIN_RIGHT_A 0
#define ID_ENCODER_DRIVE_TRAIN_RIGHT_B 1
#define ID_ENCODER_DRIVE_TRAIN_LEFT_A 2
#define ID_ENCODER_DRIVE_TRAIN_LEFT_B 3

#define ID_ENCODER_PLANETARY_A 6
#define ID_ENCODER_PLANETARY_B 7

// #########################    ID Sensor    #########################

#define ID_SENSOR_INFRA_FEEDER 5

// #########################    PID Value    #########################

// Turret
#define PLANETARY_PID_P 0.05
#define PLANETARY_PID_I 0.0
#define PLANETARY_PID_D 0.04
#define PLANETARY_PID_TOLERANCE 1.0

#define BASE_PID_P 0.01
#define BASE_PID_I 0.0
#define BASE_PID_D 0.0
#define BASE_PID_TOLERANCE 1.0

// #########################    VoltageCompensation    #########################

#define DRIVETRAIN_VOLTAGE_COMPENSATION 12.0
#define INTAKE_VOLTAGE_COMPENSATION 12.0
#define FEEDER_VOLTAGE_COMPENSATION 12.0
#define PLANETARY_VOLTAGE_COMPENSATION 10.0
#define SHOOTER_VOLTAGE_COMPENSATION 10.0
#define CLIMBER_VOLTAGE_COMPENSATION 10.0

// #########################    SmartCurrentLimit    #########################

#define DRIVETRAIN_CURRENT_LIMIT 40
#define INTAKE_CURRENT_LIMIT 40
#define FEEDER_CURRENT_LIMIT 40
#define PLANETARY_CURRENT_LIMIT 40
#define SHOOTER_CURRENT_LIMIT 40
#define CLIMBER_CURRENT_LIMIT 40

// #########################    Ramp    #########################

#define DRIVETRAIN_RAMP 0.0
#define INTAKE_RAMP 0.0
#define FEEDER_RAMP 0.0
#define PLANETARY_RAMP 0.0
#define SHOOTER_RAMP 0.1
#define CLIMBER_RAMP 0.1

// #########################    SetInvertedMotor    #########################

#define DRIVETRAIN_MOTOR_LEFT_INVERTED false
#define DRIVETRAIN_MOTOR_RIGHT_INVERTED true
#define INTAKE_MOTOR_INVERTED false
#define FEEDER_MOTOR_INVERTED false
#define PLANETARY_MOTOR_INVERTED false
#define SHOOTER_MOTOR_LEFT_INVERTED true
#define SHOOTER_MOTOR_RIGHT_INVERTED true

// #########################    SetDistancePerPulse    #########################

#define PLANETARY_DISTANCE_PER_PULSE ((1.0 / 2048.0) / 4.5) * 360.0
#define DRIVETRAIN_DISTANCE_PER_PULSE 1.0 / 2048.0
#define SHOOTER_GOALS_CONVERSION 6379 * 0.90 * (10.0 / 12.0)
#define SHOOTER_COUNT_READY 30

// #########################   SPEED  #########################

#define SHOOTER_SPEED 0.5
#define AMP_SHOOTER_SPEED 0.17
#define NEAR_SPEED_SHOOT 0.45
#define STAGE_SPEED_SHOOT 0.7
#define STOP_SHOOTER_SPEED 0.0

#define SHOOTER_SPEED_0 0.0
#define SHOOTER_SPEED_1 0.5
#define SHOOTER_SPEED_2 0.6

#define INTAKE_SPEED 1.0
#define SPIT_INTAKE_SPEED -INTAKE_SPEED
#define STOP_INTAKE_SPEED 0.0

#define CATCH_FEEDER_SPEED 1.0
#define SPIT_FEEDER_SPEED -0.5
#define STOP_FEEDER_SPEED 0.0

#define AMP_ANGLE 100
#define NEAR_ANGLE 36.5
#define TAKE_ANGLE 17
#define STAGE_ANGLE 23
#define REST_ANGLE 0.0

// #########################    CAMERA SETTINGS   ###################################
#define SHOOTER_TABLE_SIZE 15
#define ID_APRILTAG_MIDDLE 4
#define ID_APRILTAG_LEFT 3

// ##################################################################################
