cmake_minimum_required(VERSION 2.8.3)

# Project Name
project(XnVFingersGenerator)

# Detect the OS
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(WINDOWS 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(LINUX 1)
endif()

# Build path
if (WINDOWS)
  set(LIBRARY_OUTPUT_PATH bin/windows/${CMAKE_BUILD_TYPE})
elseif (LINUX)
  set(LIBRARY_OUTPUT_PATH bin/linux/${CMAKE_BUILD_TYPE})
endif()

# Includes
if (WINDOWS)
  include_directories(
  			$ENV{OPEN_NI_INCLUDE}
			include/
  )
elseif (LINUX)
  include_directories(
			/usr/include/ni/
			include/
  )
endif()

# Lib path
if (WINDOWS)
  link_directories(
			$ENV{OPEN_NI_LIB} 
  )
endif ()

# Sources
file(
	GLOB
	MOD_SRC
	src/*.cpp
)

# Create Library NiFingersGenerator
add_library(XnVFingersGenerator ${MOD_SRC})

target_link_libraries(
			XnVFingersGenerator 
			OpenNI
)
