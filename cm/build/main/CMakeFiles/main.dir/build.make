# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/linux/cm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/linux/cm/build

# Include any dependencies generated for this target.
include main/CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include main/CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include main/CMakeFiles/main.dir/flags.make

main/CMakeFiles/main.dir/main.cc.o: main/CMakeFiles/main.dir/flags.make
main/CMakeFiles/main.dir/main.cc.o: ../main/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/linux/cm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object main/CMakeFiles/main.dir/main.cc.o"
	cd /home/linux/cm/build/main && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/main.cc.o -c /home/linux/cm/main/main.cc

main/CMakeFiles/main.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cc.i"
	cd /home/linux/cm/build/main && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/linux/cm/main/main.cc > CMakeFiles/main.dir/main.cc.i

main/CMakeFiles/main.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cc.s"
	cd /home/linux/cm/build/main && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/linux/cm/main/main.cc -o CMakeFiles/main.dir/main.cc.s

main/CMakeFiles/main.dir/main.cc.o.requires:

.PHONY : main/CMakeFiles/main.dir/main.cc.o.requires

main/CMakeFiles/main.dir/main.cc.o.provides: main/CMakeFiles/main.dir/main.cc.o.requires
	$(MAKE) -f main/CMakeFiles/main.dir/build.make main/CMakeFiles/main.dir/main.cc.o.provides.build
.PHONY : main/CMakeFiles/main.dir/main.cc.o.provides

main/CMakeFiles/main.dir/main.cc.o.provides.build: main/CMakeFiles/main.dir/main.cc.o


# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cc.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main/main: main/CMakeFiles/main.dir/main.cc.o
main/main: main/CMakeFiles/main.dir/build.make
main/main: code/liblog.so
main/main: main/CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/linux/cm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable main"
	cd /home/linux/cm/build/main && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
main/CMakeFiles/main.dir/build: main/main

.PHONY : main/CMakeFiles/main.dir/build

main/CMakeFiles/main.dir/requires: main/CMakeFiles/main.dir/main.cc.o.requires

.PHONY : main/CMakeFiles/main.dir/requires

main/CMakeFiles/main.dir/clean:
	cd /home/linux/cm/build/main && $(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : main/CMakeFiles/main.dir/clean

main/CMakeFiles/main.dir/depend:
	cd /home/linux/cm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/linux/cm /home/linux/cm/main /home/linux/cm/build /home/linux/cm/build/main /home/linux/cm/build/main/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : main/CMakeFiles/main.dir/depend

