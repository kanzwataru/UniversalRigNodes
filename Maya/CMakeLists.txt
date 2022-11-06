cmake_minimum_required(VERSION 3.0)

# PART 1 - Specify the project name
set(PROJECT_NAME UniversalRigNodes)
project(${PROJECT_NAME})

# PART 2 - Include the project setting file / include path
include($ENV{DEVKIT_LOCATION}/cmake/pluginEntry.cmake)

# PART 3 - Add the source files for your executable
#set(SOURCE_FILES mcp.cpp)
file(GLOB SOURCE_FILES
	src/*.cpp
	src/*.h
	../Core/*.h
	../Core/*.cpp
)

# PART 4 - Specify the libraries in the devkit 
set(LIBRARIES
  #OpenMaya Foundation OpenMayaAnim OpenMayaFX OpenMayaRender OpenMayaUI
  OpenMaya Foundation
)

# PART 5 - specify the 3rd party package used in the project, please refer to $ENV{DEVKIT_LOCATION}/cmake/pluginEntry.cmake for the prepared packages.
#find_zlib()
#find_alembic()

# PART 6 - add the plugin building function name 
build_plugin()
