//---------------------------
// Nicolas Van der Noot & Allan Barrea
//
// Creation : 03/03/2013
// Last update : 03/03/2013
//
// Initialize the actuators models
//
//---------------------------

#include "simu_def.h"

// Initializes actuators model (stiffness and damping coefficients)
void init_actuator_model(MBSdataStruct *MBSdata)
{
    
    int i;
    
    // user variables
    UserIOStruct *uvs;
    
	// Control
	// (full of zeroes... skipped)
    
    uvs = MBSdata->user_IO;
	
	// --- KKs ---
	
	// Floating base
	uvs->Actuator_KKs[FJ_T1]  = 0.0;
	uvs->Actuator_KKs[FJ_T2]  = 0.0;
	uvs->Actuator_KKs[FJ_T3]  = 0.0;
	uvs->Actuator_KKs[FJ_R1]  = 0.0;
	uvs->Actuator_KKs[FJ_R2]  = 0.0;
	uvs->Actuator_KKs[FJ_R3]  = 0.0;

	// Right leg
	uvs->Actuator_KKs[R_HIP_SAG]  = 395.46;
	uvs->Actuator_KKs[R_HIP_LAT]  = 8400;
	uvs->Actuator_KKs[R_HIP_YAW]  = 8400;
	uvs->Actuator_KKs[R_KNEE_SAG] = 395.46;
	uvs->Actuator_KKs[R_ANK_LAT] = 8400;
	uvs->Actuator_KKs[R_ANK_SAG] = 395.46;

	#ifdef COMP_COMAN
	uvs->Actuator_KKs[R_TOE] = 5.0; // compliant foot
	#endif
	
	// Left leg
	uvs->Actuator_KKs[L_HIP_SAG] = 395.46;
	uvs->Actuator_KKs[L_HIP_LAT] = 8400;
	uvs->Actuator_KKs[L_HIP_YAW] = 8400;
	uvs->Actuator_KKs[L_KNEE_SAG] = 395.46;
	uvs->Actuator_KKs[L_ANK_LAT] = 8400;
	uvs->Actuator_KKs[L_ANK_SAG] = 395.46;

	#ifdef COMP_COMAN
	uvs->Actuator_KKs[L_TOE] = 5.0; // compliant foot
	#endif

	// Torso
	uvs->Actuator_KKs[WAIST_LAT] = 8400;
	uvs->Actuator_KKs[WAIST_SAG] = 395.46;
	uvs->Actuator_KKs[WAIST_YAW] = 395.46;

	// Right arm
	uvs->Actuator_KKs[R_SH_SAG] = 120;
	uvs->Actuator_KKs[R_SH_LAT] = 120;
	uvs->Actuator_KKs[R_SH_YAW] = 8400;
	uvs->Actuator_KKs[R_ELB] = 120;

	// Left arm
	uvs->Actuator_KKs[L_SH_SAG] = 120;
	uvs->Actuator_KKs[L_SH_LAT] = 120;
	uvs->Actuator_KKs[L_SH_YAW] = 8400;
	uvs->Actuator_KKs[L_ELB] = 120;
	
	// --- DDs ---
	
	// Floating base
	uvs->Actuator_DDs[FJ_T1] = 0.0;
	uvs->Actuator_DDs[FJ_T2] = 0.0;
	uvs->Actuator_DDs[FJ_T3] = 0.0;
	uvs->Actuator_DDs[FJ_R1] = 0.0;
	uvs->Actuator_DDs[FJ_R2] = 0.0;
	uvs->Actuator_DDs[FJ_R3] = 0.0;
	
	// Right leg
	uvs->Actuator_DDs[R_HIP_SAG] = 0.198;
	uvs->Actuator_DDs[R_HIP_LAT] = 4.2;
	uvs->Actuator_DDs[R_HIP_YAW] = 4.2;
	uvs->Actuator_DDs[R_KNEE_SAG] = 0.198;
	uvs->Actuator_DDs[R_ANK_LAT] = 4.2;
	uvs->Actuator_DDs[R_ANK_SAG] = 0.198;

	#ifdef COMP_COMAN
	uvs->Actuator_DDs[R_TOE] = 0.1;
	#endif

	// Left leg
	uvs->Actuator_DDs[L_HIP_SAG] = 0.198;
	uvs->Actuator_DDs[L_HIP_LAT] = 4.2;
	uvs->Actuator_DDs[L_HIP_YAW] = 4.2;
	uvs->Actuator_DDs[L_KNEE_SAG] = 0.198;
	uvs->Actuator_DDs[L_ANK_LAT] = 4.2;
	uvs->Actuator_DDs[L_ANK_SAG] = 0.198;

	#ifdef COMP_COMAN
	uvs->Actuator_DDs[L_TOE] = 0.1;
	#endif

	// Torso
	uvs->Actuator_DDs[WAIST_LAT] = 4.2;
	uvs->Actuator_DDs[WAIST_SAG] = 0.198;
	uvs->Actuator_DDs[WAIST_YAW] = 0.198;

	// Right arm
	uvs->Actuator_DDs[R_SH_SAG] = 0.198;
	uvs->Actuator_DDs[R_SH_LAT] = 0.198;
	uvs->Actuator_DDs[R_SH_YAW] = 4.2;
	uvs->Actuator_DDs[R_ELB] = 0.198;

	// Left arm
	uvs->Actuator_DDs[L_SH_SAG] = 0.198;
	uvs->Actuator_DDs[L_SH_LAT] = 0.198;
	uvs->Actuator_DDs[L_SH_YAW] = 4.2;
	uvs->Actuator_DDs[L_ELB] = 0.198;
	
	// --- Jdrives ---
	uvs->Actuator_Jdrives = 0.1387;
	
	// --- Ddrives ---
	uvs->Actuator_Ddrives = 25.52;
	
	// --- VTgain ---
	uvs->Actuator_VTgain = 6.175;

	// --- Conversion between joint number actuated [1-23] and real [1-29] or [1-31]
	uvs->actuated2real[R_HIP_SAG_CTRL_MOT]  = R_HIP_SAG;
	uvs->actuated2real[R_HIP_LAT_CTRL_MOT]  = R_HIP_LAT;
	uvs->actuated2real[R_HIP_YAW_CTRL_MOT]  = R_HIP_YAW;
	uvs->actuated2real[R_KNEE_SAG_CTRL_MOT] = R_KNEE_SAG;
	uvs->actuated2real[R_ANK_LAT_CTRL_MOT]  = R_ANK_LAT;
	uvs->actuated2real[R_ANK_SAG_CTRL_MOT]  = R_ANK_SAG;
	uvs->actuated2real[L_HIP_SAG_CTRL_MOT]  = L_HIP_SAG;
	uvs->actuated2real[L_HIP_LAT_CTRL_MOT]  = L_HIP_LAT;
	uvs->actuated2real[L_HIP_YAW_CTRL_MOT]  = L_HIP_YAW;
	uvs->actuated2real[L_KNEE_SAG_CTRL_MOT] = L_KNEE_SAG;
	uvs->actuated2real[L_ANK_LAT_CTRL_MOT]  = L_ANK_LAT;
	uvs->actuated2real[L_ANK_SAG_CTRL_MOT]  = L_ANK_SAG;
	uvs->actuated2real[WAIST_LAT_CTRL_MOT]  = WAIST_LAT;
	uvs->actuated2real[WAIST_SAG_CTRL_MOT]  = WAIST_SAG;
	uvs->actuated2real[WAIST_YAW_CTRL_MOT]  = WAIST_YAW;
	uvs->actuated2real[R_SH_SAG_CTRL_MOT]   = R_SH_SAG;
	uvs->actuated2real[R_SH_LAT_CTRL_MOT]   = R_SH_LAT;
	uvs->actuated2real[R_SH_YAW_CTRL_MOT]   = R_SH_YAW;
	uvs->actuated2real[R_ELB_CTRL_MOT]      = R_ELB;
	uvs->actuated2real[L_SH_SAG_CTRL_MOT]   = L_SH_SAG;
	uvs->actuated2real[L_SH_LAT_CTRL_MOT]   = L_SH_LAT;
	uvs->actuated2real[L_SH_YAW_CTRL_MOT]   = L_SH_YAW;
	uvs->actuated2real[L_ELB_CTRL_MOT]      = L_ELB;
    
    // --- Joint limits ---
    
	// Entered here in degrees
	// (source: coman_Hardware_slides.pdf)
	// for joint numbers, cf. Robotran model.
	// coman_Hardware_slides.pdf is not complete: it only gives information
	// about the legs and nothing about the upper body (including torso).
	// Common sense and observation on the simulations helps a lot to define the bounds.
	// Sometimes, I extend the bounds a little for simulation safety.
    
	// To understand coman_Hardware_slides.pdf:
	// flex/ext = flexion/extension = rotation about the Y axis (= sag = R2)
	// abd/add = abduction/adduction = rotation about the X axis (= lat = R1)
	// rotation = rotation about the Z axis (= yaw = R3)
    
	// Warning ! For the X axis, the joints limits are inverted between both legs.
	// --> take symmetric bounds to ease the thing.
	
	// ---- Min joint limits ---- //
	
	// Floating base
	uvs->joint_limits_min[FJ_T1]  = 0.0;
	uvs->joint_limits_min[FJ_T2]  = 0.0;
	uvs->joint_limits_min[FJ_T3]  = 0.0;
	uvs->joint_limits_min[FJ_R1]  = 0.0;
	uvs->joint_limits_min[FJ_R2]  = 0.0;
	uvs->joint_limits_min[FJ_R3]  = 0.0;
    
	// Right leg
	uvs->joint_limits_min[R_HIP_SAG]  = -120.0;
	uvs->joint_limits_min[R_HIP_LAT]  = -80.0;
	uvs->joint_limits_min[R_HIP_YAW]  = -50.0;
	uvs->joint_limits_min[R_KNEE_SAG] = -10.0;
	uvs->joint_limits_min[R_ANK_LAT] = -35.0;
	uvs->joint_limits_min[R_ANK_SAG] = -90.0;
	#ifdef COMP_COMAN
	uvs->joint_limits_min[R_TOE] = -90.0;
	#endif
	
	// Left leg
	uvs->joint_limits_min[L_HIP_SAG] = -120.0;
	uvs->joint_limits_min[L_HIP_LAT] = -35.0;
	uvs->joint_limits_min[L_HIP_YAW] = -50.0;
	uvs->joint_limits_min[L_KNEE_SAG] = -10.0;
	uvs->joint_limits_min[L_ANK_LAT] = -35.0;
	uvs->joint_limits_min[L_ANK_SAG] = -90.0;
	#ifdef COMP_COMAN
	uvs->joint_limits_min[L_TOE] = -90.0;
	#endif
    
	// Torso
	uvs->joint_limits_min[WAIST_LAT] = -70.0;
	uvs->joint_limits_min[WAIST_SAG] = -60.0;
	uvs->joint_limits_min[WAIST_YAW] = -90.0;
    
	// Right arm
	uvs->joint_limits_min[R_SH_SAG] = -90.0;
	uvs->joint_limits_min[R_SH_LAT] = -120.0;
	uvs->joint_limits_min[R_SH_YAW] = -50.0;
	uvs->joint_limits_min[R_ELB] = -120.0;
    
	// Left arm
	uvs->joint_limits_min[L_SH_SAG] = -90.0;
	uvs->joint_limits_min[L_SH_LAT] = -35.0;
	uvs->joint_limits_min[L_SH_YAW] = -50.0;
	uvs->joint_limits_min[L_ELB] = -120.0;
	

	// ---- Max joint limits ---- //
    
	// Floating base
	uvs->joint_limits_max[FJ_T1]  = 0.0;
	uvs->joint_limits_max[FJ_T2]  = 0.0;
	uvs->joint_limits_max[FJ_T3]  = 0.0;
	uvs->joint_limits_max[FJ_R1]  = 0.0;
	uvs->joint_limits_max[FJ_R2]  = 0.0;
	uvs->joint_limits_max[FJ_R3]  = 0.0;
    
	// Right leg
	uvs->joint_limits_max[R_HIP_SAG]  = 70.0;
	uvs->joint_limits_max[R_HIP_LAT]  = 35.0;
	uvs->joint_limits_max[R_HIP_YAW]  = 50.0;
	uvs->joint_limits_max[R_KNEE_SAG] = 120.0;
	uvs->joint_limits_max[R_ANK_LAT] = 35.0;
	uvs->joint_limits_max[R_ANK_SAG] = 90.0;
	#ifdef COMP_COMAN
	uvs->joint_limits_max[R_TOE] = 45.0;
	#endif
	
	// Left leg
	uvs->joint_limits_max[L_HIP_SAG] = 70.0;
	uvs->joint_limits_max[L_HIP_LAT] = 80.0;
	uvs->joint_limits_max[L_HIP_YAW] = 50.0;
	uvs->joint_limits_max[L_KNEE_SAG] = 120.0;
	uvs->joint_limits_max[L_ANK_LAT] = 35.0;
	uvs->joint_limits_max[L_ANK_SAG] = 90.0;
	#ifdef COMP_COMAN
	uvs->joint_limits_max[L_TOE] = 45.0;
	#endif
    
	// Torso
	uvs->joint_limits_max[WAIST_LAT] = 70.0;
	uvs->joint_limits_max[WAIST_SAG] = 90.0;
	uvs->joint_limits_max[WAIST_YAW] = 90.0;
    
	// Right arm
	uvs->joint_limits_max[R_SH_SAG] = 90.0;
	uvs->joint_limits_max[R_SH_LAT] = 35.0;
	uvs->joint_limits_max[R_SH_YAW] = 50.0;
	uvs->joint_limits_max[R_ELB] = 45.0;
    
	// Left arm
	uvs->joint_limits_max[L_SH_SAG] = 90.0;
	uvs->joint_limits_max[L_SH_LAT] = 120.0;
	uvs->joint_limits_max[L_SH_YAW] = 50.0;
	uvs->joint_limits_max[L_ELB] = 45.0;
    
	// Conversion from degrees to radians
	for(i=1; i<=COMAN_NB_JOINT_TOTAL; i++)
	{
		uvs->joint_limits_min[i] = uvs->joint_limits_min[i]*PI/180.0;
		uvs->joint_limits_max[i] = uvs->joint_limits_max[i]*PI/180.0;
	}
}

