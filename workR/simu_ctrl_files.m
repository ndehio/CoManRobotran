function[simulation_headers, controller_headers, simulation_files, controller_files] = simu_ctrl_files()

simulation_headers = {...
    'simu_def.h'...
    };

controller_headers = {...
    'controller_def.h'...
    'ControllersStruct.h'...
    };

simulation_files = {...
    'simu_outputs.c'...
    'simu_controller_loop.c'...
    'controller_inputs.c'...
    'controller_outputs.c'...
    'center_of_pressure.c'...
    'init_GCM.c'...
    'init_actuator_model.c'...
    'impedance_controller.c'...
    'simu_useful_functions.c'...
    'stop_simu.c'...
    'opti_fitness.c'...
    };

controller_files = {...
    'ControllersStruct.c'...
    'controller_init.c'...    
    'controller_loop.c'...    
    'controller_functions.c'...
    'handle_inputs.c'...
    'get_ref.c'...
    'walk_states.c'...
    'init_opti.c'...
    'yaw_leg_torque.c'...
    'lat_leg_torque.c'...
    'upright_sag_leg.c'...
    'sag_leg_torque.c'...
    'HG_main.c'...
    'HG_f_l.c'...
    'HG_torques.c'...
    'HG_pose.c'...
    'HG_initialization.c'...
    'HG_l_mtu.c'...
    'HG_get_waiting_tab.c'...
    'HG_f_v.c'...
    'HG_l_ce.c'...
    'HG_inputs_delay.c'...
    'HG_forces.c'...
    'HG_stim_act.c'...
    'HG_stimulation_choice.c'...
    'HG_stimulation.c'...
    'HG_noise.c'...
    'HG_main_lower_steps.c'...
    'arm_trunk_pos_ref.c'...    
    'metabolic_energy.c'...
    };
end 