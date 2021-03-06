#
# author: Nicolas Van der Noot
# Feb 27 2014
#
# Main CMakeLists, used to configure the project
#


## ---- FLAGS ----  ##

# Yarp
option(FLAG_YARP
	"Robotran YARP Interface", OFF)

# Optimization
option (FLAG_OPTI 
        "Optimization" OFF)

# compile with C++
option (FLAG_CXX  
        "Use C++" OFF) 

# let the use choose the compiler
option (FLAG_COMPILER  
        "Modify compilers properties" OFF) 

# use dirdynared (otherwise: accelred) -> accelred still not implemented
option (FLAG_DIRDYNARED 
        "Dirdynared" ON) 

# print messages in the terminal...
option (FLAG_PRINT_REPORT  
        "Print Report" ON) 

# write the .anim file and the debug .txt vectors
option (FLAG_WRITE_FILES 
        "Write Files" ON) 
 
# automatic generation of the 'ControllersStruct.h/.c' and 'user_sf_IO.h/.c' files
option (FLAG_GENERATE 
        "Generate ControllersStruct, user_sf_IO" OFF) 

# run the simulation in real-time
option (FLAG_REAL_TIME 
        "Real time" ON) 

# use the SDL library to plot real-time graphs and to handle the user inputs (keyboard...)
option (FLAG_SDL 
        "SDL" ON) 

# use JNI (Java Native Interface) to see the simulation in real-time
option (FLAG_JNI 
        "JNI" ON)

# run the simulation in real-time
option (FLAG_GCM 
        "Use custom-made GCM" ON) 

# run the simulation in real-time
option (FLAG_STOP 
        "Stop simulation" ON) 

# Simbody
option (FLAG_SIMBODY 
        "Simbody" OFF) 

# Compliant feet
option (FLAG_COMPLIANT 
        "Compliant feet" OFF) 

# 3D model
option (FLAG_3D 
        "3D model" ON) 

# Release flag
option (FLAG_RELEASE 
        "Release flag" ON) 

# flags dependencies
if (NOT FLAG_CXX)
	set(FLAG_SIMBODY OFF)
endif (NOT FLAG_CXX)

if (NOT FLAG_REAL_TIME)
	set(FLAG_SDL OFF)
	set(FLAG_JNI OFF)
endif (NOT FLAG_REAL_TIME)

if (FLAG_OPTI)
	set(FLAG_WRITE_FILES OFF)
	set(FLAG_GENERATE OFF)
	set(FLAG_REAL_TIME OFF)
	set(FLAG_SDL OFF)
	set(FLAG_JNI OFF)
endif (FLAG_OPTI)


## ---- PROJECT MAIN CONFIGURATIONS ---- ##

# CMake minimum version
cmake_minimum_required(VERSION 2.8.7)

# Build required robotran_yarp_plugin
if (FLAG_YARP)
#### Find YARP, require that YARP version is at least ICUB_REQYARP_VERSION
	find_package(YARP REQUIRED)
    message(STATUS " YARP is version: ${YARP_VERSION} tweak number ${YARP_VERSION_TWEAK}")    
	add_definitions(${YARP_DEFINES})

    # pick up yarp's cmake scripts
    list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})
    include(YarpInstallationHelpers)

    # add yarp include directories
    include_directories( ${YARP_INCLUDE_DIRS}) 
    
endif (FLAG_YARP)

if (FLAG_COMPILER)
	set( CMAKE_C_COMPILER gcc-4.4 )
	set( CMAKE_CXX_COMPILER g++-4.4 )
	set(CMAKE_C_FLAGS_RELEASE "-O3")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif (FLAG_COMPILER)

# project name
project (STANDALONE)


# message to display the project name
message(STATUS "Processing ${PROJECT_NAME}")

# define the location of all the 'Find<module>.cmake' files
set(COMANSIM_MODULE_PATH ${PROJECT_SOURCE_DIR}/src/other/conf)
set(CMAKE_MODULE_PATH ${COMANSIM_MODULE_PATH})

if (FLAG_CXX)
	add_definitions( -DCXX )
endif (FLAG_CXX)

if (FLAG_OPTI)
	add_definitions( -DOPTI )
endif (FLAG_OPTI)

# for Unix: display all the warnings, except the ones related to /* -- */
if (UNIX)
	set(CMAKE_C_FLAGS "-g -Wall -Wno-comment")
	set(CMAKE_CXX_FLAGS "-g -Wall -Wno-comment")
endif (UNIX)

# use Release version and not the Debug one (faster)
if (FLAG_RELEASE)
	set(CMAKE_BUILD_TYPE Release)
else (FLAG_RELEASE)
	set(CMAKE_BUILD_TYPE Debug)
endif (FLAG_RELEASE)
		

## ---- AUTOMATIC GENERATION  ('ControllersStruct.h/.c' and 'user_sf_IO.h/.c')  ---- ##

if (FLAG_GENERATE)

	# ControllersStruct.h/.c
	set(CONTROLLERSSTRCT_H ${PROJECT_SOURCE_DIR}/src/project/controller_files/ControllersStruct.h)
	set(CONTROLLERSSTRCT_C ${PROJECT_SOURCE_DIR}/src/project/controller_files/ControllersStruct.c)

	# user_sf_IO.h/.c
	set(USER_SF_IO_H ${PROJECT_SOURCE_DIR}/src/project/user_files/user_sf_IO.h)
	set(USER_SF_IO_C ${PROJECT_SOURCE_DIR}/src/project/user_files/user_sf_IO.c)

	# input .txt files
	set(CONTROL_VAR_TXT ${PROJECT_SOURCE_DIR}/src/project/varState/control_variables.txt)
	set(SIMU_VAR_TXT ${PROJECT_SOURCE_DIR}/src/project/varState/simu_variables.txt)

	# re-generate ControllersStruct.h/.c
	add_custom_command (
	  OUTPUT ${CONTROLLERSSTRCT_H} ${CONTROLLERSSTRCT_C}
	  COMMAND Gen_state_var ctrl
	  DEPENDS ${CONTROL_VAR_TXT}
	)

	# re-generate user_sf_IO.h/.c
	add_custom_command (
	  OUTPUT ${USER_SF_IO_H} ${USER_SF_IO_C}
	  COMMAND Gen_state_var simu
	  DEPENDS ${SIMU_VAR_TXT}
	)

	# check if re-generation needed
	add_custom_target(CheckGeneration ALL 
		DEPENDS ${CONTROLLERSSTRCT_H} ${USER_SF_IO_H})
	
endif (FLAG_GENERATE)

 

## ---- CUSTOM FUNCTIONS ---- ##


# These files will not be compiled or included in the project
set(CUR_ITEM "")

set(SRC_FILES_NOT_COMPILED "mbs_invdyna_CoMan_23Dof_V4.c")
set(HEADERS_NOT_INCLUDED "mbs_invdyna_CoMan_23Dof_V4.h")

if (FLAG_DIRDYNARED)

	set(SRC_FILES_NOT_COMPILED ${SRC_FILES_NOT_COMPILED} "mbs_accelred_CoMan_23Dof_V4.c")
	set(HEADERS_NOT_INCLUDED ${HEADERS_NOT_INCLUDED} "mbs_accelred_CoMan_23Dof_V4.h")

else (FLAG_DIRDYNARED)

	set(SRC_FILES_NOT_COMPILED ${SRC_FILES_NOT_COMPILED} "mbs_dirdyna_CoMan_23Dof_V4.c")
	set(HEADERS_NOT_INCLUDED ${HEADERS_NOT_INCLUDED} "mbs_dirdyna_CoMan_23Dof_V4.h")

endif (FLAG_DIRDYNARED)

if (FLAG_CXX)
	set(SRC_FILES_NOT_COMPILED ${SRC_FILES_NOT_COMPILED} "model_main.c")
else (FLAG_CXX)
	set(SRC_FILES_NOT_COMPILED ${SRC_FILES_NOT_COMPILED} "model_main.cpp")
endif (FLAG_CXX)

if (FLAG_SIMBODY)
	set(SRC_FILES_NOT_COMPILED ${SRC_FILES_NOT_COMPILED} "loop_simulation.c")
else (FLAG_SIMBODY)
	set(SRC_FILES_NOT_COMPILED ${SRC_FILES_NOT_COMPILED} "loop_simulation.cpp")
endif (FLAG_SIMBODY)
	

# function to return 1 if the element 'CUR_ITEM' is present in list 'HEADERS_NOT_INCLUDED'
function(header_present_in_list FOUND_IN_LIST)
	set(FOUND_IN_LIST 0 PARENT_SCOPE)
	foreach(LIST_ITEM ${HEADERS_NOT_INCLUDED})
		if (${LIST_ITEM} STREQUAL ${CUR_ITEM})
    		set(FOUND_IN_LIST 1 PARENT_SCOPE)
    	endif (${LIST_ITEM} STREQUAL ${CUR_ITEM})
	endforeach(LIST_ITEM)
endfunction()

# function to return 1 if the element 'CUR_ITEM' is present in list 'SRC_FILES_NOT_COMPILED'
function(src_present_in_list FOUND_IN_LIST)
	set(FOUND_IN_LIST 0 PARENT_SCOPE)
	foreach(LIST_ITEM ${SRC_FILES_NOT_COMPILED})
		if (${LIST_ITEM} STREQUAL ${CUR_ITEM})
    		set(FOUND_IN_LIST 1 PARENT_SCOPE)
    	endif (${LIST_ITEM} STREQUAL ${CUR_ITEM})
	endforeach(LIST_ITEM)
endfunction()


## -- Main sources files -- ##

# function to list all source files (.c) in the src/project/ and src/generic/ directories, 
# recursing into sub-directories
function(list_source_files_c SOURCE_FILES_C)
    file(GLOB_RECURSE SOURCE_FILES_TMP     		
    		"${PROJECT_SOURCE_DIR}/src/generic/*.c" 
    		"${PROJECT_SOURCE_DIR}/src/project/*.c")
    foreach(SRC_FILE ${SOURCE_FILES_TMP})
    	get_filename_component(CUR_ITEM ${SRC_FILE} NAME)
    	src_present_in_list(FOUND_IN_LIST)
    	if (NOT FOUND_IN_LIST)
    		set(SOURCES ${SOURCES} ${SRC_FILE})
    	endif (NOT FOUND_IN_LIST)
    endforeach(SRC_FILE)
    set(SOURCE_FILES_C ${SOURCES} PARENT_SCOPE)
endfunction()

# function to list all source files (.cpp) in the src/project/ and src/generic/ directories, 
# recursing into sub-directories
function(list_source_files_cpp SOURCE_FILES_CPP)
    file(GLOB_RECURSE SOURCE_FILES_TMP     		
    		"${PROJECT_SOURCE_DIR}/src/generic/*.cc"
    		"${PROJECT_SOURCE_DIR}/src/generic/*.cpp"
    		"${PROJECT_SOURCE_DIR}/src/project/*.cc"
    		"${PROJECT_SOURCE_DIR}/src/project/*.cpp")
    foreach(SRC_FILE ${SOURCE_FILES_TMP})
    	get_filename_component(CUR_ITEM ${SRC_FILE} NAME)
    	src_present_in_list(FOUND_IN_LIST)
    	if (NOT FOUND_IN_LIST)
    		set(SOURCES ${SOURCES} ${SRC_FILE})
    	endif (NOT FOUND_IN_LIST)
    endforeach(SRC_FILE)
    set(SOURCE_FILES_CPP ${SOURCES} PARENT_SCOPE)
endfunction()

# function to list all paths to header files in the src/project/ and src/generic/ directories, 
# recursing into sub-directories (includes)
function(list_full_include_directories FULL_INCLUDE_DIRECTORIES)
    file(GLOB_RECURSE FULL_INCLUDE_DIRECTORIES_TMP RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
    		"${PROJECT_SOURCE_DIR}/src/generic/*.h" 
    		"${PROJECT_SOURCE_DIR}/src/generic/*.hpp"
    		"${PROJECT_SOURCE_DIR}/src/project/*.h" 
    		"${PROJECT_SOURCE_DIR}/src/project/*.hpp")
    set(DIR_LIST "")
    foreach(FILE_PATH ${FULL_INCLUDE_DIRECTORIES_TMP})
    	get_filename_component(DIR_PATH ${FILE_PATH} PATH)
    	get_filename_component(CUR_ITEM ${FILE_PATH} NAME)    	
    	header_present_in_list(FOUND_IN_LIST)
    	if (NOT FOUND_IN_LIST)
    		set(DIR_LIST ${DIR_LIST} ${DIR_PATH})
    	endif (NOT FOUND_IN_LIST)
    endforeach(FILE_PATH)
    list(REMOVE_DUPLICATES DIR_LIST) 
    set(FULL_INCLUDE_DIRECTORIES ${DIR_LIST} PARENT_SCOPE)
endfunction()


## -- Optimization files -- ##

# function to list all source files (.c) in the src/project/ and src/generic/ directories, 
# recursing into sub-directories
function(list_opti_files_c OPTI_FILES_C)
    file(GLOB_RECURSE SOURCE_FILES_TMP     		
    		"${PROJECT_SOURCE_DIR}/src/other/opti/functions/*.c")
    foreach(SRC_FILE ${SOURCE_FILES_TMP})
    	get_filename_component(CUR_ITEM ${SRC_FILE} NAME)
    	src_present_in_list(FOUND_IN_LIST)
    	if (NOT FOUND_IN_LIST)
    		set(SOURCES ${SOURCES} ${SRC_FILE})
    	endif (NOT FOUND_IN_LIST)
    endforeach(SRC_FILE)
    set(OPTI_FILES_C ${SOURCES} PARENT_SCOPE)
endfunction()

# function to list all source files (.cpp) in the src/project/ and src/generic/ directories, 
# recursing into sub-directories
function(list_opti_files_cpp OPTI_FILES_CPP)
    file(GLOB_RECURSE SOURCE_FILES_TMP     		
    		"${PROJECT_SOURCE_DIR}/src/other/opti/functions/*.cc"
    		"${PROJECT_SOURCE_DIR}/src/other/opti/functions/*.cpp")
    foreach(SRC_FILE ${SOURCE_FILES_TMP})
    	get_filename_component(CUR_ITEM ${SRC_FILE} NAME)
    	src_present_in_list(FOUND_IN_LIST)
    	if (NOT FOUND_IN_LIST)
    		set(SOURCES ${SOURCES} ${SRC_FILE})
    	endif (NOT FOUND_IN_LIST)
    endforeach(SRC_FILE)
    set(OPTI_FILES_CPP ${SOURCES} PARENT_SCOPE)
endfunction()

# function to list all paths to header files in the src/project/ and src/generic/ directories, 
# recursing into sub-directories (includes)
function(list_opti_include_directories OPTI_INCLUDE_DIRECTORIES)
    file(GLOB_RECURSE FULL_INCLUDE_DIRECTORIES_TMP RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
    		"${PROJECT_SOURCE_DIR}/src/other/opti/functions/*.h" 
    		"${PROJECT_SOURCE_DIR}/src/other/opti/functions/*.hpp")
    set(DIR_LIST "")
    foreach(FILE_PATH ${FULL_INCLUDE_DIRECTORIES_TMP})
    	get_filename_component(DIR_PATH ${FILE_PATH} PATH)
    	get_filename_component(CUR_ITEM ${FILE_PATH} NAME)    	
    	header_present_in_list(FOUND_IN_LIST)
    	if (NOT FOUND_IN_LIST)
    		set(DIR_LIST ${DIR_LIST} ${DIR_PATH})
    	endif (NOT FOUND_IN_LIST)
    endforeach(FILE_PATH)
    list(REMOVE_DUPLICATES DIR_LIST) 
    set(OPTI_INCLUDE_DIRECTORIES ${DIR_LIST} PARENT_SCOPE)
endfunction()

## ---- FIND PATHS AND EXTERNAL LIBRARIES ---- ##

# main source project path (to print in 'cmake_config.h') 
set (PROJECT_ABS_PATH ${PROJECT_SOURCE_DIR})
set (BINARY_ABS_PATH ${PROJECT_BINARY_DIR})

# not a Simulink simulation (Standalone)
add_definitions( -DCMEX )

# load a xml file to intialize the dynamics structure
add_definitions( -DLOAD_XML )

# Ground Contact Model activated
if (FLAG_GCM)
	add_definitions( -DGCM_MT )
endif (FLAG_GCM)

# stop the simulation
if (FLAG_STOP)
	add_definitions( -DFLAG_STOP )
endif (FLAG_STOP)



# Libxml2 (always required)
find_package(Libxml2 REQUIRED)
if (LIBXML2_FOUND)
	include_directories (${LIBXML2_INCLUDE_PATH})	
	message( "\n  >> Libxml2 found")
else (LIBXML2_FOUND)
	message( "\n  >> Libxml2 not found, modify src/other/conf/FindLibxml2.cmake")
endif(LIBXML2_FOUND)

message("      -> INC : ${LIBXML2_INCLUDE_PATH}")
message("      -> LIB : ${LIBXML2_LIBRARIES}\n")

# dirdynared or accelred
if (FLAG_DIRDYNARED)
	add_definitions( -DDIRDYNARED )
else (FLAG_DIRDYNARED)
	add_definitions( -DACCELRED )
endif (FLAG_DIRDYNARED)

# flag for Unix systems (used in some source files)
if (UNIX)
	add_definitions( -DUNIX )
endif (UNIX)

# write the .anim file and the debug .txt vectors
if (FLAG_WRITE_FILES)
	add_definitions( -DWRITE_FILES )
endif (FLAG_WRITE_FILES)

# print messages in the terminal...
if (FLAG_PRINT_REPORT)
	add_definitions( -DPRINT_REPORT )
endif (FLAG_PRINT_REPORT)

if (FLAG_COMPLIANT)
	add_definitions( -DCOMP_COMAN )
endif (FLAG_COMPLIANT)

# real-time features
if (FLAG_REAL_TIME)

	# real-time flag
	add_definitions( -DREAL_TIME )

	# SDL
	if (FLAG_SDL)

		add_definitions( -DSDL )

		find_package(SDL2 REQUIRED)
		if (SDL2_FOUND)
			include_directories (${SDL2_INCLUDE_PATH})
			message( "\n  >> SDL 2.0 found")		
		else (SDL2_FOUND)
			message( "\n>> SDL 2.0 not found, modify src/other/conf/FindSDL2.cmake")		
		endif (SDL2_FOUND)

		message("      -> INC : ${SDL2_INCLUDE_PATH}")
		message("      -> LIB : ${SDL2_LIBRARIES}\n")

		# SDL_ttf
		find_package(SDL2_ttf REQUIRED)
		if (SDL2TTF_FOUND)				
			include_directories (${SDL2TTF_INCLUDE_PATH})
			message( "\n  >> SDL 2.0 ttf found")				
		else (SDL2TTF_FOUND)
			message( "\n  >> SDL 2.0 ttf not found, modify src/other/conf/FindSDL2_ttf.cmake")
		endif (SDL2TTF_FOUND)

		message("      -> INC : ${SDL2TTF_INCLUDE_PATH}")
		message("      -> LIB : ${SDL2TTF_LIBRARIES}\n")

	endif (FLAG_SDL)

	# JNI (Java Native Interface)
	if (FLAG_JNI)

		add_definitions( -DJNI )

		find_package(JNI REQUIRED)

		if (JNI_FOUND)
			include_directories (${JNI_INCLUDE_PATH})
			message( "\n  >> JNI found")
		else (JNI_FOUND)
			message( "\n  >> JNI not found, modify src/other/conf/FindJNI.cmake")
		endif (JNI_FOUND)

		message("      -> INC : ${JNI_INCLUDE_PATH}")
		message("      -> LIB : ${JNI_LIBRARIES}\n")

		# Java 3D
		find_package(J3D REQUIRED)

		if (J3D_FOUND)
			# path to some Java 3D files (to print in 'cmake_config.h') 
			set (J3D_ABS_PATH ${J3D_PATH})
			message( "\n  >> Java 3D found")
		else (J3D_FOUND)
			message( "\n  >> Java 3D not found, modify src/other/conf/FindJ3D.cmake")
		endif (J3D_FOUND)

		message("      -> PATH : ${J3D_PATH}\n")

	endif (FLAG_JNI)

endif (FLAG_REAL_TIME)

# Simbody
if (FLAG_SIMBODY)
	add_definitions( -DSIMBODY )

	find_package(Simbody REQUIRED)
	if (SIMBODY_FOUND)
			include_directories (${SIMBODY_INCLUDE_PATH})
			message( "\n  >> Simbody found")		
		else (SIMBODY_FOUND)
			message( "\n>> Simbody not found, modify src/other/conf/FindSimbody.cmake")		
		endif (SIMBODY_FOUND)

		message("      -> INC : ${SIMBODY_INCLUDE_PATH}")
		message("      -> LIB : ${SIMBODY_LIBRARIES}\n")
endif (FLAG_SIMBODY)


# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/src/other/conf/cmake_config.h.in"
  "${PROJECT_BINARY_DIR}/src/other/conf/cmake_config.h"
  )
# 'cmake_config.h.in' is in the 'conf' folder
include_directories (${PROJECT_BINARY_DIR}/src/other/conf)

# copy all the dll (except 'jvm.dll') used for Windows
# these dll files are copied in the Executable directory
if (WIN32)
	file(COPY ${PROJECT_SOURCE_DIR}/src/other/win64_include_lib/dll/ DESTINATION ${CMAKE_BINARY_DIR}/Debug)
endif (WIN32)


# Take the good version of the CoMan
if (FLAG_COMPLIANT)

	file(COPY ${PROJECT_SOURCE_DIR}/src/other/CoMan_versions/Compliant_feet/Symbolic_files/ DESTINATION ${PROJECT_SOURCE_DIR}/src/project)

	if (FLAG_3D)
		file(COPY ${PROJECT_SOURCE_DIR}/src/other/CoMan_versions/Compliant_feet/Model_standalone_3D/ DESTINATION ${PROJECT_SOURCE_DIR}/src/project)
	else (FLAG_3D)
		file(COPY ${PROJECT_SOURCE_DIR}/src/other/CoMan_versions/Compliant_feet/Model_standalone_2D/ DESTINATION ${PROJECT_SOURCE_DIR}/src/project)
	endif (FLAG_3D)

	if (FLAG_REAL_TIME)
		file(COPY ${PROJECT_SOURCE_DIR}/../dataR/CoMan_versions/Compliant_feet/ DESTINATION ${PROJECT_SOURCE_DIR}/../dataR)
	endif (FLAG_REAL_TIME)

else (FLAG_COMPLIANT)

	file(COPY ${PROJECT_SOURCE_DIR}/src/other/CoMan_versions/Rigid_feet/Symbolic_files/ DESTINATION ${PROJECT_SOURCE_DIR}/src/project)

	if (FLAG_3D)
		file(COPY ${PROJECT_SOURCE_DIR}/src/other/CoMan_versions/Rigid_feet/Model_standalone_3D/ DESTINATION ${PROJECT_SOURCE_DIR}/src/project)
	else (FLAG_3D)
		file(COPY ${PROJECT_SOURCE_DIR}/src/other/CoMan_versions/Rigid_feet/Model_standalone_2D/ DESTINATION ${PROJECT_SOURCE_DIR}/src/project)
	endif (FLAG_3D)

	if (FLAG_REAL_TIME)
		file(COPY ${PROJECT_SOURCE_DIR}/../dataR/CoMan_versions/Rigid_feet/ DESTINATION ${PROJECT_SOURCE_DIR}/../dataR)
	endif (FLAG_REAL_TIME)

endif (FLAG_COMPLIANT)

# add locations of other Makefiles
add_subdirectory (src/)
add_subdirectory (src/other/varState/)

if (FLAG_OPTI)
	add_subdirectory (src/other/opti/code_generation/)
endif (FLAG_OPTI)
