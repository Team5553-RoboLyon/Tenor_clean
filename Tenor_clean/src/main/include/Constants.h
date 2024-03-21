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
