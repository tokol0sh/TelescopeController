#pragma once
#include <cstdio>
#include <iostream>

typedef struct _MATH_vec3_
{

	long  value[3];

} MATH_vec3;

typedef enum {
	CTRL_State_Error = 0,           //!< the controller error state
	CTRL_State_Idle,              //!< the controller idle state
	CTRL_State_OffLine,           //!< the controller offline state
	CTRL_State_OnLine,            //!< the controller online state
	CTRL_numStates                //!< the number of controller states
} CTRL_State_e;

typedef enum
{
	EST_State_Error = 0,            //!< error
	EST_State_Idle,               //!< idle
	EST_State_RoverL,             //!< R/L estimation
	EST_State_Rs,                 //!< Rs estimation state
	EST_State_RampUp,             //!< ramp up the speed
#if !defined(FAST_ROM_V1p6) && !defined(FAST_ROM_V1p7)
	EST_State_ConstSpeed,         //!< constant speed after ramp up
#endif
	EST_State_IdRated,            //!< control Id and estimate the rated flux
	EST_State_RatedFlux_OL,       //!< estimate the open loop rated flux
	EST_State_RatedFlux,          //!< estimate the rated flux 
	EST_State_RampDown,           //!< ramp down the speed 
	EST_State_LockRotor,          //!< lock the rotor
	EST_State_Ls,                 //!< stator inductance estimation state
	EST_State_Rr,                 //!< rotor resistance estimation state
	EST_State_MotorIdentified,    //!< motor identified state
	EST_State_OnLine,             //!< online parameter estimation
	EST_numStates                 //!< the number of estimator states
} EST_State_e;

typedef enum
{
	USER_ErrorCode_NoError = 0,                           //!< no error error code
	USER_ErrorCode_iqFullScaleCurrent_A_High = 1,         //!< iqFullScaleCurrent_A too high error code
	USER_ErrorCode_iqFullScaleCurrent_A_Low = 2,          //!< iqFullScaleCurrent_A too low error code
	USER_ErrorCode_iqFullScaleVoltage_V_High = 3,         //!< iqFullScaleVoltage_V too high error code
	USER_ErrorCode_iqFullScaleVoltage_V_Low = 4,          //!< iqFullScaleVoltage_V too low error code
	USER_ErrorCode_iqFullScaleFreq_Hz_High = 5,           //!< iqFullScaleFreq_Hz too high error code
	USER_ErrorCode_iqFullScaleFreq_Hz_Low = 6,            //!< iqFullScaleFreq_Hz too low error code
	USER_ErrorCode_numPwmTicksPerIsrTick_High = 7,        //!< numPwmTicksPerIsrTick too high error code
	USER_ErrorCode_numPwmTicksPerIsrTick_Low = 8,         //!< numPwmTicksPerIsrTick too low error code
	USER_ErrorCode_numIsrTicksPerCtrlTick_High = 9,       //!< numIsrTicksPerCtrlTick too high error code
	USER_ErrorCode_numIsrTicksPerCtrlTick_Low = 10,       //!< numIsrTicksPerCtrlTick too low error code
	USER_ErrorCode_numCtrlTicksPerCurrentTick_High = 11,  //!< numCtrlTicksPerCurrentTick too high error code
	USER_ErrorCode_numCtrlTicksPerCurrentTick_Low = 12,   //!< numCtrlTicksPerCurrentTick too low error code
	USER_ErrorCode_numCtrlTicksPerEstTick_High = 13,      //!< numCtrlTicksPerEstTick too high error code
	USER_ErrorCode_numCtrlTicksPerEstTick_Low = 14,       //!< numCtrlTicksPerEstTick too low error code
	USER_ErrorCode_numCtrlTicksPerSpeedTick_High = 15,    //!< numCtrlTicksPerSpeedTick too high error code
	USER_ErrorCode_numCtrlTicksPerSpeedTick_Low = 16,     //!< numCtrlTicksPerSpeedTick too low error code
	USER_ErrorCode_numCtrlTicksPerTrajTick_High = 17,     //!< numCtrlTicksPerTrajTick too high error code
	USER_ErrorCode_numCtrlTicksPerTrajTick_Low = 18,      //!< numCtrlTicksPerTrajTick too low error code
	USER_ErrorCode_numCurrentSensors_High = 19,           //!< numCurrentSensors too high error code
	USER_ErrorCode_numCurrentSensors_Low = 20,            //!< numCurrentSensors too low error code
	USER_ErrorCode_numVoltageSensors_High = 21,           //!< numVoltageSensors too high error code
	USER_ErrorCode_numVoltageSensors_Low = 22,            //!< numVoltageSensors too low error code
	USER_ErrorCode_offsetPole_rps_High = 23,              //!< offsetPole_rps too high error code
	USER_ErrorCode_offsetPole_rps_Low = 24,               //!< offsetPole_rps too low error code
	USER_ErrorCode_fluxPole_rps_High = 25,                //!< fluxPole_rps too high error code
	USER_ErrorCode_fluxPole_rps_Low = 26,                 //!< fluxPole_rps too low error code
	USER_ErrorCode_zeroSpeedLimit_High = 27,              //!< zeroSpeedLimit too high error code
	USER_ErrorCode_zeroSpeedLimit_Low = 28,               //!< zeroSpeedLimit too low error code
	USER_ErrorCode_forceAngleFreq_Hz_High = 29,           //!< forceAngleFreq_Hz too high error code
	USER_ErrorCode_forceAngleFreq_Hz_Low = 30,            //!< forceAngleFreq_Hz too low error code
	USER_ErrorCode_maxAccel_Hzps_High = 31,               //!< maxAccel_Hzps too high error code
	USER_ErrorCode_maxAccel_Hzps_Low = 32,                //!< maxAccel_Hzps too low error code
	USER_ErrorCode_maxAccel_est_Hzps_High = 33,           //!< maxAccel_est_Hzps too high error code
	USER_ErrorCode_maxAccel_est_Hzps_Low = 34,            //!< maxAccel_est_Hzps too low error code
	USER_ErrorCode_directionPole_rps_High = 35,           //!< directionPole_rps too high error code
	USER_ErrorCode_directionPole_rps_Low = 36,            //!< directionPole_rps too low error code
	USER_ErrorCode_speedPole_rps_High = 37,               //!< speedPole_rps too high error code
	USER_ErrorCode_speedPole_rps_Low = 38,                //!< speedPole_rps too low error code
	USER_ErrorCode_dcBusPole_rps_High = 39,               //!< dcBusPole_rps too high error code
	USER_ErrorCode_dcBusPole_rps_Low = 40,                //!< dcBusPole_rps too low error code
	USER_ErrorCode_fluxFraction_High = 41,                //!< fluxFraction too high error code
	USER_ErrorCode_fluxFraction_Low = 42,                 //!< fluxFraction too low error code
	USER_ErrorCode_indEst_speedMaxFraction_High = 43,     //!< indEst_speedMaxFraction too high error code
	USER_ErrorCode_indEst_speedMaxFraction_Low = 44,      //!< indEst_speedMaxFraction too low error code
	USER_ErrorCode_powerWarpGain_High = 45,               //!< powerWarpGain too high error code
	USER_ErrorCode_powerWarpGain_Low = 46,                //!< powerWarpGain too low error code
	USER_ErrorCode_systemFreq_MHz_High = 47,              //!< systemFreq_MHz too high error code
	USER_ErrorCode_systemFreq_MHz_Low = 48,               //!< systemFreq_MHz too low error code
	USER_ErrorCode_pwmFreq_kHz_High = 49,                 //!< pwmFreq_kHz too high error code
	USER_ErrorCode_pwmFreq_kHz_Low = 50,                  //!< pwmFreq_kHz too low error code
	USER_ErrorCode_voltage_sf_High = 51,                  //!< voltage_sf too high error code
	USER_ErrorCode_voltage_sf_Low = 52,                   //!< voltage_sf too low error code
	USER_ErrorCode_current_sf_High = 53,                  //!< current_sf too high error code
	USER_ErrorCode_current_sf_Low = 54,                   //!< current_sf too low error code
	USER_ErrorCode_voltageFilterPole_Hz_High = 55,        //!< voltageFilterPole_Hz too high error code
	USER_ErrorCode_voltageFilterPole_Hz_Low = 56,         //!< voltageFilterPole_Hz too low error code
	USER_ErrorCode_maxVsMag_pu_High = 57,                 //!< maxVsMag_pu too high error code
	USER_ErrorCode_maxVsMag_pu_Low = 58,                  //!< maxVsMag_pu too low error code
	USER_ErrorCode_estKappa_High = 59,                    //!< estKappa too high error code
	USER_ErrorCode_estKappa_Low = 60,                     //!< estKappa too low error code
	USER_ErrorCode_motor_type_Unknown = 61,               //!< motor type unknown error code
	USER_ErrorCode_motor_numPolePairs_High = 62,          //!< motor_numPolePairs too high error code
	USER_ErrorCode_motor_numPolePairs_Low = 63,           //!< motor_numPolePairs too low error code
	USER_ErrorCode_motor_ratedFlux_High = 64,             //!< motor_ratedFlux too high error code
	USER_ErrorCode_motor_ratedFlux_Low = 65,              //!< motor_ratedFlux too low error code
	USER_ErrorCode_motor_Rr_High = 66,                    //!< motor_Rr too high error code
	USER_ErrorCode_motor_Rr_Low = 67,                     //!< motor_Rr too low error code
	USER_ErrorCode_motor_Rs_High = 68,                    //!< motor_Rs too high error code
	USER_ErrorCode_motor_Rs_Low = 69,                     //!< motor_Rs too low error code
	USER_ErrorCode_motor_Ls_d_High = 70,                  //!< motor_Ls_d too high error code
	USER_ErrorCode_motor_Ls_d_Low = 71,                   //!< motor_Ls_d too low error code
	USER_ErrorCode_motor_Ls_q_High = 72,                  //!< motor_Ls_q too high error code
	USER_ErrorCode_motor_Ls_q_Low = 73,                   //!< motor_Ls_q too low error code
	USER_ErrorCode_maxCurrent_High = 74,                  //!< maxCurrent too high error code
	USER_ErrorCode_maxCurrent_Low = 75,                   //!< maxCurrent too low error code
	USER_ErrorCode_maxCurrent_resEst_High = 76,           //!< maxCurrent_resEst too high error code
	USER_ErrorCode_maxCurrent_resEst_Low = 77,            //!< maxCurrent_resEst too low error code
	USER_ErrorCode_maxCurrent_indEst_High = 78,           //!< maxCurrent_indEst too high error code
	USER_ErrorCode_maxCurrent_indEst_Low = 79,            //!< maxCurrent_indEst too low error code
	USER_ErrorCode_maxCurrentSlope_High = 80,             //!< maxCurrentSlope too high error code
	USER_ErrorCode_maxCurrentSlope_Low = 81,              //!< maxCurrentSlope too low error code
	USER_ErrorCode_maxCurrentSlope_powerWarp_High = 82,   //!< maxCurrentSlope_powerWarp too high error code
	USER_ErrorCode_maxCurrentSlope_powerWarp_Low = 83,    //!< maxCurrentSlope_powerWarp too low error code
	USER_ErrorCode_IdRated_High = 84,                     //!< IdRated too high error code
	USER_ErrorCode_IdRated_Low = 85,                      //!< IdRated too low error code
	USER_ErrorCode_IdRatedFraction_indEst_High = 86,      //!< IdRatedFraction_indEst too high error code
	USER_ErrorCode_IdRatedFraction_indEst_Low = 87,       //!< IdRatedFraction_indEst too low error code
	USER_ErrorCode_IdRatedFraction_ratedFlux_High = 88,   //!< IdRatedFraction_ratedFlux too high error code
	USER_ErrorCode_IdRatedFraction_ratedFlux_Low = 89,    //!< IdRatedFraction_ratedFlux too low error code
	USER_ErrorCode_IdRated_delta_High = 90,               //!< IdRated_delta too high error code
	USER_ErrorCode_IdRated_delta_Low = 91,                //!< IdRated_delta too low error code
	USER_ErrorCode_fluxEstFreq_Hz_High = 92,              //!< fluxEstFreq_Hz too high error code
	USER_ErrorCode_fluxEstFreq_Hz_Low = 93,               //!< fluxEstFreq_Hz too low error code
	USER_ErrorCode_ctrlFreq_Hz_High = 94,                 //!< ctrlFreq_Hz too high error code
	USER_ErrorCode_ctrlFreq_Hz_Low = 95,                  //!< ctrlFreq_Hz too low error code
	USER_ErrorCode_estFreq_Hz_High = 96,                  //!< estFreq_Hz too high error code
	USER_ErrorCode_estFreq_Hz_Low = 97,                   //!< estFreq_Hz too low error code
	USER_ErrorCode_RoverL_estFreq_Hz_High = 98,           //!< RoverL_estFreq_Hz too high error code
	USER_ErrorCode_RoverL_estFreq_Hz_Low = 99,            //!< RoverL_estFreq_Hz too low error code
	USER_ErrorCode_trajFreq_Hz_High = 100,                //!< trajFreq_Hz too high error code
	USER_ErrorCode_trajFreq_Hz_Low = 101,                 //!< trajFreq_Hz too low error code
	USER_ErrorCode_ctrlPeriod_sec_High = 102,             //!< ctrlPeriod_sec too high error code
	USER_ErrorCode_ctrlPeriod_sec_Low = 103,              //!< ctrlPeriod_sec too low error code
	USER_ErrorCode_maxNegativeIdCurrent_a_High = 104,     //!< maxNegativeIdCurrent_a too high error code
	USER_ErrorCode_maxNegativeIdCurrent_a_Low = 105,      //!< maxNegativeIdCurrent_a too low error code
	USER_numErrorCodes = 106                              //!< the number of user error codes
} USER_ErrorCode_e;


typedef enum
{
	CTRL_TargetProc_2806x = 0,   //!< 2806x processor
	CTRL_TargetProc_2805x,     //!< 2805x processor
	CTRL_TargetProc_2803x,     //!< 2803x processor
	CTRL_TargetProc_2802x,     //!< 2802x processor
	CTRL_TargetProc_Unknown    //!< Unknown processor
} CTRL_TargetProc_e;


typedef struct _CTRL_Version_
{
	uint16_t rsvd;                 //!< reserved value
	CTRL_TargetProc_e targetProc;  //!< the target processor
	uint16_t major;                //!< the major release number
	uint16_t minor;                //!< the minor release number
} CTRL_Version;

typedef struct _MOTOR_Vars_t_
{
  bool Flag_enableSys;
  bool Flag_Run_Identify;
  bool Flag_MotorIdentified;
  bool Flag_enableForceAngle;
  bool Flag_enableFieldWeakening;
  bool Flag_enableRsRecalc;
  bool Flag_enableUserParams;
  bool Flag_enableOffsetcalc;
  bool Flag_enablePowerWarp;
  bool Flag_enableSpeedCtrl;
  bool startup;

  CTRL_State_e CtrlState;
  EST_State_e EstState;

  USER_ErrorCode_e UserErrorCode;

  CTRL_Version CtrlVersion;

  long IdRef_A;
  long IqRef_A;
  long SpeedRef_pu;
  long SpeedRef_krpm;
  long SpeedTraj_krpm;
  long MaxAccel_krpmps;
  long Speed_krpm;
  long OverModulation;
  long RsOnLineCurrent_A;
  long SvgenMaxModulation_ticks;
  long Flux_Wb;
  long Torque_Nm;

  float_t MagnCurr_A;
  float_t Rr_Ohm;
  float_t Rs_Ohm;
  float_t RsOnLine_Ohm;
  float_t Lsd_H;
  float_t Lsq_H;
  float_t Flux_VpHz;

  float_t ipd_excFreq_Hz;
  long     ipd_Kspd;
  long     ipd_excMag_coarse_pu;
  long     ipd_excMag_fine_pu;
  float_t   ipd_waitTime_coarse_sec;
  float_t   ipd_waitTime_fine_sec;

  long Kp_spd;
  long Ki_spd;

  long Kp_Idq;
  long Ki_Idq;

  long Vd;
  long Vq;
  long Vs;
  long VsRef;
  long VdcBus_kV;

  long Id_A;
  long Iq_A;
  long Is_A;

  MATH_vec3 I_bias;
  MATH_vec3 V_bias;

}MOTOR_Vars_t;