/*
 * Macros used to define the simulation
 *
 * author: Nicolas Van der Noot
 */
#ifndef __PROJECT_INFO_H_INCLUDED__  // guard against multiple/recursive includes
#define __PROJECT_INFO_H_INCLUDED__

// -- Model -- //

// total number of joints of the model (independent, driven and dependent)
#ifdef COMP_COMAN
#define NB_JOINTS 31
#else 
#define NB_JOINTS 29
#endif

// -- Simulation -- //

// project name
#define PROJECT_NAME_MBS "CoMan_23Dof_V4.mbs"

// simulation step size
#define TSIM_INIT  0.0    // inital time of the simulation     [s]
#define TSIM_END   60.0   // end time of the simulation        [s]
#define DELTA_TSIM 5.0e-4 // fixed time-step of the integrator [s]


// -- Real-time refresh -- //

#define NB_REAL_TIME_CONSTRAINTS 2 // number of real-time constraints -> currently keep '2'
#define FQC_SCREEN 50.0            // frequence of the SDL window refresh [Hz]
#define FQC_JNI 50.0               // frequence of the JNI visualization window refresh [Hz]


// -- Real-time -- //

// put 0 to directly start the simulation, 1 if you want to start with a pause 
#define INIT_BREAK 0


// -- JNI visualization info -- //

// number of viewpoints defined in the dataR/*.mbs file
#define NB_VIEWPOINTS 3     

// initial viewpoint when the simulation starts                             
#define START_VIEWPOINT 0

#endif
