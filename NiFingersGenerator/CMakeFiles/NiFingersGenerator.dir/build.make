# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dd/Desktop/Air/NiFingersGenerator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dd/Desktop/Air/NiFingersGenerator

# Include any dependencies generated for this target.
include CMakeFiles/NiFingersGenerator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/NiFingersGenerator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/NiFingersGenerator.dir/flags.make

CMakeFiles/NiFingersGenerator.dir/src/FingersGenerator.cpp.o: CMakeFiles/NiFingersGenerator.dir/flags.make
CMakeFiles/NiFingersGenerator.dir/src/FingersGenerator.cpp.o: src/FingersGenerator.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dd/Desktop/Air/NiFingersGenerator/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/NiFingersGenerator.dir/src/FingersGenerator.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/NiFingersGenerator.dir/src/FingersGenerator.cpp.o -c /home/dd/Desktop/Air/NiFingersGenerator/src/FingersGenerator.cpp

CMakeFiles/NiFingersGenerator.dir/src/FingersGenerator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NiFingersGenerator.dir/src/FingersGenerator.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dd/Desktop/Air/NiFingersGenerator/src/FingersGenerator.cpp > CMakeFiles/NiFingersGenerator.dir/src/FingersGenerator.cpp.i

CMakeFiles/NiFingersGenerator.dir/src/FingersGenerator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NiFingersGenerator.dir/src/FingersGenerator.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dd/Desktop/Air/NiFingersGenerator/src/FingersGenerator.cpp -o CMakeFiles/NiFingersGenerator.dir/src/FingersGenerator.cpp.s

CMakeFiles/NiFingersGenerator.dir/src/FingersGenerator.cpp.o.requires:
.PHONY : CMakeFiles/NiFingersGenerator.dir/src/FingersGenerator.cpp.o.requires

CMakeFiles/NiFingersGenerator.dir/src/FingersGenerator.cpp.o.provides: CMakeFiles/NiFingersGenerator.dir/src/FingersGenerator.cpp.o.requires
	$(MAKE) -f CMakeFiles/NiFingersGenerator.dir/build.make CMakeFiles/NiFingersGenerator.dir/src/FingersGenerator.cpp.o.provides.build
.PHONY : CMakeFiles/NiFingersGenerator.dir/src/FingersGenerator.cpp.o.provides

CMakeFiles/NiFingersGenerator.dir/src/FingersGenerator.cpp.o.provides.build: CMakeFiles/NiFingersGenerator.dir/src/FingersGenerator.cpp.o
.PHONY : CMakeFiles/NiFingersGenerator.dir/src/FingersGenerator.cpp.o.provides.build

# Object files for target NiFingersGenerator
NiFingersGenerator_OBJECTS = \
"CMakeFiles/NiFingersGenerator.dir/src/FingersGenerator.cpp.o"

# External object files for target NiFingersGenerator
NiFingersGenerator_EXTERNAL_OBJECTS =

bin/libNiFingersGenerator.so: CMakeFiles/NiFingersGenerator.dir/src/FingersGenerator.cpp.o
bin/libNiFingersGenerator.so: CMakeFiles/NiFingersGenerator.dir/build.make
bin/libNiFingersGenerator.so: CMakeFiles/NiFingersGenerator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library bin/libNiFingersGenerator.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/NiFingersGenerator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/NiFingersGenerator.dir/build: bin/libNiFingersGenerator.so
.PHONY : CMakeFiles/NiFingersGenerator.dir/build

CMakeFiles/NiFingersGenerator.dir/requires: CMakeFiles/NiFingersGenerator.dir/src/FingersGenerator.cpp.o.requires
.PHONY : CMakeFiles/NiFingersGenerator.dir/requires

CMakeFiles/NiFingersGenerator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/NiFingersGenerator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/NiFingersGenerator.dir/clean

CMakeFiles/NiFingersGenerator.dir/depend:
	cd /home/dd/Desktop/Air/NiFingersGenerator && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dd/Desktop/Air/NiFingersGenerator /home/dd/Desktop/Air/NiFingersGenerator /home/dd/Desktop/Air/NiFingersGenerator /home/dd/Desktop/Air/NiFingersGenerator /home/dd/Desktop/Air/NiFingersGenerator/CMakeFiles/NiFingersGenerator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NiFingersGenerator.dir/depend

