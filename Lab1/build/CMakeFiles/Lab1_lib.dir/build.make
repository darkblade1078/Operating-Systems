# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/darkblade/Documents/GitHub/Operating-Systems/Lab1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/darkblade/Documents/GitHub/Operating-Systems/Lab1/build

# Include any dependencies generated for this target.
include CMakeFiles/Lab1_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Lab1_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Lab1_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lab1_lib.dir/flags.make

CMakeFiles/Lab1_lib.dir/src/process.cpp.o: CMakeFiles/Lab1_lib.dir/flags.make
CMakeFiles/Lab1_lib.dir/src/process.cpp.o: /home/darkblade/Documents/GitHub/Operating-Systems/Lab1/src/process.cpp
CMakeFiles/Lab1_lib.dir/src/process.cpp.o: CMakeFiles/Lab1_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/darkblade/Documents/GitHub/Operating-Systems/Lab1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Lab1_lib.dir/src/process.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lab1_lib.dir/src/process.cpp.o -MF CMakeFiles/Lab1_lib.dir/src/process.cpp.o.d -o CMakeFiles/Lab1_lib.dir/src/process.cpp.o -c /home/darkblade/Documents/GitHub/Operating-Systems/Lab1/src/process.cpp

CMakeFiles/Lab1_lib.dir/src/process.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Lab1_lib.dir/src/process.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/darkblade/Documents/GitHub/Operating-Systems/Lab1/src/process.cpp > CMakeFiles/Lab1_lib.dir/src/process.cpp.i

CMakeFiles/Lab1_lib.dir/src/process.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Lab1_lib.dir/src/process.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/darkblade/Documents/GitHub/Operating-Systems/Lab1/src/process.cpp -o CMakeFiles/Lab1_lib.dir/src/process.cpp.s

CMakeFiles/Lab1_lib.dir/src/system_calls.cpp.o: CMakeFiles/Lab1_lib.dir/flags.make
CMakeFiles/Lab1_lib.dir/src/system_calls.cpp.o: /home/darkblade/Documents/GitHub/Operating-Systems/Lab1/src/system_calls.cpp
CMakeFiles/Lab1_lib.dir/src/system_calls.cpp.o: CMakeFiles/Lab1_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/darkblade/Documents/GitHub/Operating-Systems/Lab1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Lab1_lib.dir/src/system_calls.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lab1_lib.dir/src/system_calls.cpp.o -MF CMakeFiles/Lab1_lib.dir/src/system_calls.cpp.o.d -o CMakeFiles/Lab1_lib.dir/src/system_calls.cpp.o -c /home/darkblade/Documents/GitHub/Operating-Systems/Lab1/src/system_calls.cpp

CMakeFiles/Lab1_lib.dir/src/system_calls.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Lab1_lib.dir/src/system_calls.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/darkblade/Documents/GitHub/Operating-Systems/Lab1/src/system_calls.cpp > CMakeFiles/Lab1_lib.dir/src/system_calls.cpp.i

CMakeFiles/Lab1_lib.dir/src/system_calls.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Lab1_lib.dir/src/system_calls.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/darkblade/Documents/GitHub/Operating-Systems/Lab1/src/system_calls.cpp -o CMakeFiles/Lab1_lib.dir/src/system_calls.cpp.s

# Object files for target Lab1_lib
Lab1_lib_OBJECTS = \
"CMakeFiles/Lab1_lib.dir/src/process.cpp.o" \
"CMakeFiles/Lab1_lib.dir/src/system_calls.cpp.o"

# External object files for target Lab1_lib
Lab1_lib_EXTERNAL_OBJECTS =

libLab1_lib.so: CMakeFiles/Lab1_lib.dir/src/process.cpp.o
libLab1_lib.so: CMakeFiles/Lab1_lib.dir/src/system_calls.cpp.o
libLab1_lib.so: CMakeFiles/Lab1_lib.dir/build.make
libLab1_lib.so: CMakeFiles/Lab1_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/darkblade/Documents/GitHub/Operating-Systems/Lab1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library libLab1_lib.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lab1_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lab1_lib.dir/build: libLab1_lib.so
.PHONY : CMakeFiles/Lab1_lib.dir/build

CMakeFiles/Lab1_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Lab1_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Lab1_lib.dir/clean

CMakeFiles/Lab1_lib.dir/depend:
	cd /home/darkblade/Documents/GitHub/Operating-Systems/Lab1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/darkblade/Documents/GitHub/Operating-Systems/Lab1 /home/darkblade/Documents/GitHub/Operating-Systems/Lab1 /home/darkblade/Documents/GitHub/Operating-Systems/Lab1/build /home/darkblade/Documents/GitHub/Operating-Systems/Lab1/build /home/darkblade/Documents/GitHub/Operating-Systems/Lab1/build/CMakeFiles/Lab1_lib.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Lab1_lib.dir/depend

