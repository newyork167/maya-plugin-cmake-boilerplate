cmake_minimum_required(VERSION 3.7)

# Set the project name - This is used later in this script to set filenames
project(FluidSimPlugin)

# Set the cmake modules path to find the cmake Find* files
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)

# Set the source and library file paths
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

# Make a shaders directory to put GLSL files
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/shaders")

# Set this to the Maya version you have installed as it will use this version code to 
# determine file paths in the FindMaya.cmake script
set(MAYA_VERSION 2019 CACHE STRING "Maya version")

if(WIN32)
    set(MAYA_PLUGIN_OUTPUT_DIR "C:/Users/Newyork167/Documents/maya/plug-ins")
    set(MAYA_PYTHON_BIN "C:/Program Files/Autodesk/Maya${MAYA_VERSION}/bin/mayapy.exe")
elseif(APPLE)
	# This is a generic folder created by Maya for dumping plug-ins into on OSX
    set(MAYA_PLUGIN_OUTPUT_DIR "/Users/Shared/Autodesk/maya/plug-ins")
    set(MAYA_PYTHON_BIN "/Applications/Autodesk/maya${MAYA_VERSION}/Maya.app/Contents/bin/mayapy")
endif(WIN32)

# Glob together all the source code / GLSL files
file(GLOB_RECURSE SOURCE_FILES
    ${SRC_DIR}/*.h
    ${SRC_DIR}/*.cpp
    ${SRC_DIR}/*.vert
    ${SRC_DIR}/*.frag
)

# Use the modules/FindMaya.cmake finder
find_package(Maya REQUIRED)

# Add Shaders
macro(makeLink src dest target)
    add_custom_command(TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E create_symlink ${src} ${dest}  DEPENDS  ${dest} COMMENT "mklink ${src} -> ${dest}")
endmacro()

file(GLOB_RECURSE SHADERS
        "${SRC_DIR}/*.vert"
        "${SRC_DIR}/*.frag"
        )
foreach(SHADER ${SHADERS})
    message(${SHADER})
    if(WIN32)
		# For windows we will use the built in configure_file method to copy shaders over
        get_filename_component(SHADERNAME ${SHADER} NAME)
        message(STATUS ${SHADERNAME})
		configure_file(${SHADER} ${CMAKE_CURRENT_BINARY_DIR}/shaders/${SHADERNAME} COPYONLY)
    elseif(UNIX AND NOT APPLE)
		# If *nix use the copy command
        file(COPY ${SHADER} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shaders/)
    elseif(APPLE)
		# If apple use the custom command macro from before this
        # create symbolic link for *.vs *.fs *.gs
        get_filename_component(SHADERNAME ${SHADER} NAME)
        makeLink(${SHADER} ${CMAKE_CURRENT_BINARY_DIR}/shaders/${SHADERNAME} ${PROJECT_NAME})
    endif(WIN32)
endforeach(SHADER)

# Link MLL Plugin File
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE Maya::Maya)
target_include_directories(${PROJECT_NAME} PRIVATE Maya::Maya)
MAYA_PLUGIN(${PROJECT_NAME})

# Run python script to unload this plugin from Maya
message("Unloading Plugin from Maya")
SET(PLUGIN_LOADER_ARGS "-p ${PROJECT_NAME}" "-u")
execute_process(COMMAND ${MAYA_PYTHON_BIN} scripts/load_plugin.py ${PLUGIN_LOADER_ARGS}
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

# Set output directory
if(WIN32)
	set(PLUGIN_OUTPUT_PATH ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.mll)
	message("Copying ${PLUGIN_OUTPUT_PATH} to ${MAYA_PLUGIN_OUTPUT_DIR}/${PLUGINNAME} if exists!")
	if(EXISTS ${PLUGIN_OUTPUT_PATH})
		configure_file(${PROJECT_BINARY_DIR}/${PROJECT_NAME}.mll ${MAYA_PLUGIN_OUTPUT_DIR}/${PLUGINNAME} COPYONLY)
    endif()
elseif(APPLE)
    set(PLUGIN_OUTPUT_PATH ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bundle)
    message("Copying ${PLUGIN_OUTPUT_PATH} to ${MAYA_PLUGIN_OUTPUT_DIR}/${PLUGINNAME} if exists!")
    if(EXISTS ${PLUGIN_OUTPUT_PATH})
        makeLink(${PLUGIN_OUTPUT_PATH} ${MAYA_PLUGIN_OUTPUT_DIR}/${PROJECT_NAME}.bundle ${PROJECT_NAME})
    endif()
endif(WIN32)

# Run python script to load the plugin back into Maya
message("Loading Plugin from Maya")
SET(PLUGIN_LOADER_ARGS "-p ${PROJECT_NAME}" "-l")
execute_process(COMMAND ${MAYA_PYTHON_BIN} scripts/load_plugin.py  ${PLUGIN_LOADER_ARGS}
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})