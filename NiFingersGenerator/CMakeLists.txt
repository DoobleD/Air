cmake_minimum_required(VERSION 2.8.3)

# Project Name
project(XnVFingersGenerator)

# Build path
set(LIBRARY_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

# Detect the OS
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(WINDOWS 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(LINUX 1)
endif()

# Find Boost. See FindBoost.cmake module for more information (location CMAKE_DIR/shared/modules/)
#set(Boost_USE_STATIC_LIBS        ON)
#set(Boost_USE_MULTITHREADED      ON)
#set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost COMPONENTS REQUIRED)

# Includes
if (WINDOWS)
  include_directories(
			$ENV{OPEN_NI_INCLUDE} 
			include/
  )
elseif (LINUX)
  include_directories(
			${Boost_INCLUDE_DIRS}
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
add_library(XnVFingersGenerator SHARED ${MOD_SRC})

target_link_libraries(
			XnVFingersGenerator 
			OpenNI
)