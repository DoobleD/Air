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
add_definitions(-DDEBUG_MOD)

# Build path
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

# Find SFML. See FindSFML.cmake module for more information (location: AIR_DIR/cmake_modules/)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(SFML COMPONENTS graphics window system REQUIRED)

# Include path
include_directories(
			${SFML_INCLUDE_DIRS} 
		    	include
)
if (WINDOWS)
  include_directories(
			$ENV{OPEN_NI_INCLUDE} 
			$ENV{XN_NITE_INSTALL_PATH}/Include 
			include/win32
  )
elseif (LINUX)
  include_directories(
			/usr/include/nite/
			/usr/include/ni/
			include/unix
  )
endif()

# Lib path
link_directories(
			${SFML_LIBRARY_DIRS}
)
if (WINDOWS)
  link_directories(
			$ENV{OPEN_NI_LIB} 
		 	$ENV{XN_NITE_INSTALL_PATH}/Lib 
  )
endif ()

# Sources
file(			GLOB 
			BASE_SRC 
			src/*
)
if (WINDOWS)
  file(
			GLOB 
			OS_SRC 
			src/win32/*
  )
elseif (LINUX)
  file(
			GLOB 
			OS_SRC 
			src/unix/*
  )
endif ()

# Creates executable
add_executable(Air ${BASE_SRC} ${OS_SRC})

# Link libraries
target_link_libraries(
			Air 
			OpenNI 
			XnVNite_1_3_1
			${SFML_LIBRARIES} 
)
