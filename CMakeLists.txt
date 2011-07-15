cmake_minimum_required(VERSION 2.8.3)

# Project Name
project(Air)

# Uncomment to compile in debug mod
add_definitions(-DDEBUG_MOD)

# Build path
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

# Find Boost. See FindBoost.cmake module for more information (location CMAKE_DIR/shared/modules/)
#set(Boost_USE_STATIC_LIBS        ON)
#set(Boost_USE_MULTITHREADED      ON)
#set(Boost_USE_STATIC_RUNTIME    OFF)
#find_package(Boost COMPONENTS thread REQUIRED)

# Find SFML. See FindSFML.cmake module for more information (location: AIR_DIR/cmake_modules/)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(SFML COMPONENTS graphics window system REQUIRED)

#Include path
include_directories(
			if (WIN32)
			  $ENV{OPEN_NI_INCLUDE} 
		    	  $ENV{XN_NITE_INSTALL_PATH}/Include 
			elseif (UNIX)
			  /usr/include/nite/
			  /usr/include/ni/
			endif
#			${Boost_INCLUDE_DIRS} 
			${SFML_INCLUDE_DIRS} 
		    	include
)

#Lib path
link_directories(
			if (WIN32)
			  $ENV{OPEN_NI_LIB} 
		 	  $ENV{XN_NITE_INSTALL_PATH}/Lib 
			endif
#			${Boost_LIBRARY_DIRS} 
			${SFML_LIBRARY_DIRS}
)

# Sources
file(
	GLOB_RECURSE
	SOURCE_FILES
	src/*
)

# Creates executable
add_executable(Air ${SOURCE_FILES})

# Link libraries
target_link_libraries(
			Air 
			OpenNI 
			XnVNite_1_3_1
#			${Boost_LIBRARIES} 
			${SFML_LIBRARIES} 
)
