#pragma once
#include <cstdio>
#include <iostream>


typedef enum {
	VBUS_VOLTAGE, // RO
	ELEC_RAD_PER_ENC, // RO
	M0_POS_SETPOINT, // RW
	M0_POS_GAIN, // RW
	M0_VEL_SETPOINT, // RW
	M0_VEL_GAIN, // RW
	M0_VEL_INTEGRATOR_GAIN, // RW
	M0_VEL_INTEGRATOR_CURRENT, // RW
	M0_VEL_LIMIT, // RW
	M0_CURRENT_SETPOINT, // RW
	M0_CALIBRATION_CURRENT, // RW
	M0_PHASE_INDUCTANCE, // RO
	M0_PHASE_RESISTANCE, // RO
	M0_CURRENT_MEAS_PHB, // RO
	M0_CURRENT_MEAS_PHC, // RO
	M0_DC_CALIB_PHB, // RW
	M0_DC_CALIB_PHC, // RW
	M0_SHUNT_CONDUCTANCE, // RW
	M0_PHASE_CURRENT_REV_GAIN, // RW
	M0_CURRENT_CONTROL_CURRENT_LIM, // RW
	M0_CURRENT_CONTROL_P_GAIN, // RW
	M0_CURRENT_CONTROL_I_GAIN, // RW
	M0_CURRENT_CONTROL_V_CURRENT_CONTROL_INTEGRAL_D, // RW
	M0_CURRENT_CONTROL_V_CURRENT_CONTROL_INTEGRAL_Q, // RW
	M0_CURRENT_CONTROL_IBUS, // RO
	M0_ROTOR_PHASE, // RO
	M0_ROTOR_PLL_POS, // RW
	M0_ROTOR_PLL_VEL, // RW
	M0_ROTOR_PLL_KP, // RW
	M0_ROTOR_PLL_KI, // RW
	M1_POS_SETPOINT, // RW
	M1_POS_GAIN, // RW
	M1_VEL_SETPOINT, // RW
	M1_VEL_GAIN, // RW
	M1_VEL_INTEGRATOR_GAIN, // RW
	M1_VEL_INTEGRATOR_CURRENT, // RW
	M1_VEL_LIMIT, // RW
	M1_CURRENT_SETPOINT, // RW
	M1_CALIBRATION_CURRENT, // RW
	M1_PHASE_INDUCTANCE, // RO
	M1_PHASE_RESISTANCE, // RO
	M1_CURRENT_MEAS_PHB, // RO
	M1_CURRENT_MEAS_PHC, // RO
	M1_DC_CALIB_PHB, // RW
	M1_DC_CALIB_PHC, // RW
	M1_SHUNT_CONDUCTANCE, // RW
	M1_PHASE_CURRENT_REV_GAIN, // RW
	M1_CURRENT_CONTROL_CURRENT_LIM, // RW
	M1_CURRENT_CONTROL_P_GAIN, // RW
	M1_CURRENT_CONTROL_I_GAIN, // RW
	M1_CURRENT_CONTROL_V_CURRENT_CONTROL_INTEGRAL_D, // RW
	M1_CURRENT_CONTROL_V_CURRENT_CONTROL_INTEGRAL_Q, // RW
	M1_CURRENT_CONTROL_IBUS, // RO
	M1_ROTOR_PHASE, // RO
	M1_ROTOR_PLL_POS, // RW
	M1_ROTOR_PLL_VEL, // RW
	M1_ROTOR_PLL_KP, // RW
	M1_ROTOR_PLL_KI, // RW
} Exposed_floats_t;


typedef struct {
	float vbus_voltage; // ro
	float elec_rad_per_enc; // ro
	float M0_pos_setpoint; // rw
	float M0_pos_gain; // rw
	float M0_vel_setpoint; // rw
	float M0_vel_gain; // rw
	float M0_vel_integrator_gain; // rw
	float M0_vel_integrator_current; // rw
	float M0_vel_limit; // rw
	float M0_current_setpoint; // rw
	float M0_calibration_current; // rw
	float M0_phase_inductance; // ro
	float M0_phase_resistance; // ro
	float M0_current_meas_phB; // ro
	float M0_current_meas_phC; // ro
	float M0_DC_calib_phB; // rw
	float M0_DC_calib_phC; // rw
	float M0_shunt_conductance; // rw
	float M0_phase_current_rev_gain; // rw
	float M0_current_control_current_lim; // rw
	float M0_current_control_p_gain; // rw
	float M0_current_control_i_gain; // rw
	float M0_current_control_v_current_control_integral_d; // rw
	float M0_current_control_v_current_control_integral_q; // rw
	float M0_current_control_Ibus; // ro
	float M0_rotor_phase; // ro
	float M0_rotor_pll_pos; // rw
	float M0_rotor_pll_vel; // rw
	float M0_rotor_pll_kp; // rw
	float M0_rotor_pll_ki; // rw
	float M1_pos_setpoint; // rw
	float M1_pos_gain; // rw
	float M1_vel_setpoint; // rw
	float M1_vel_gain; // rw
	float M1_vel_integrator_gain; // rw
	float M1_vel_integrator_current; // rw
	float M1_vel_limit; // rw
	float M1_current_setpoint; // rw
	float M1_calibration_current; // rw
	float M1_phase_inductance; // ro
	float M1_phase_resistance; // ro
	float M1_current_meas_phB; // ro
	float M1_current_meas_phC; // ro
	float M1_DC_calib_phB; // rw
	float M1_DC_calib_phC; // rw
	float M1_shunt_conductance; // rw
	float M1_phase_current_rev_gain; // rw
	float M1_current_control_current_lim; // rw
	float M1_current_control_p_gain; // rw
	float M1_current_control_i_gain; // rw
	float M1_current_control_v_current_control_integral_d; // rw
	float M1_current_control_v_current_control_integral_q; // rw
	float M1_current_control_Ibus; // ro
	float M1_rotor_phase; // ro
	float M1_rotor_pll_pos; // rw
	float M1_rotor_pll_vel; // rw
	float M1_rotor_pll_kp; // rw
	float M1_rotor_pll_ki; // rw
} Exposed_floats;

