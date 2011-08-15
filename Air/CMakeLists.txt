cmake_minimum_required(VERSION 2.8.3)

# Project Name
project(Air)

# Detect the OS
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(WINDOWS 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(LINUX 1)
endif()
  
# Uncomment to compile in debug mod
add_definitions(-DDEBUG_MOD -ggdb3)

# Build path
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

# Find SFML. See FindSFML.cmake module for more information (location: AIR_DIR/cmake_modules/)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(SFML COMPONENTS graphics window system REQUIRED)

# Include path
include_directories(
			${SFML_INCLUDE_DIRS} 
			../NiFingersGenerator/include
		    	include
)
if (WINDOWS)
  include_directories(
			$ENV{OPEN_NI_INCLUDE} 
			$ENV{XN_NITE_INSTALL_PATH}/Include 
  )
elseif (LINUX)
  include_directories(
			/usr/include/nite/
			/usr/include/ni/
  )
endif()

# Lib path
link_directories(
			${SFML_LIBRARY_DIRS}
			../NiFingersGenerator/bin
)
if (WINDOWS)
  link_directories(
			$ENV{OPEN_NI_LIB} 
		 	$ENV{XN_NITE_INSTALL_PATH}/Lib 
			../NiFingersGenerator/bin/bin/Release
			../NiFingersGenerator/bin/bin/Debug
  )
endif ()

# Sources
file(			GLOB 
			BASE_SRC 
			src/*.cpp
)
if (WINDOWS)
  file(
			GLOB 
			OS_SRC 
			src/OS/win32/*.cpp
  )
elseif (LINUX)
  file(
			GLOB 
			OS_SRC 
			src/OS/unix/*.cpp
  )
endif ()

# Creates executable
add_executable(Air ${BASE_SRC} ${OS_SRC})

if (WINDOWS)
  # Link libraries
  target_link_libraries(
			Air 
			OpenNI 
			XnVNite_1_4_1
			XnVFingersGenerator
			${SFML_LIBRARIES}
  )
endif()

if (LINUX)
  # Link libraries
  target_link_libraries(
			Air 
			OpenNI 
			XnVNite_1_4_1
			XnVFingersGenerator
			${SFML_LIBRARIES}
			-lXtst
  )
endif()
