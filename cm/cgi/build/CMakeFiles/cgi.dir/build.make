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
CMAKE_SOURCE_DIR = /home/linux/cm/cgi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/linux/cm/cgi/build

# Include any dependencies generated for this target.
include CMakeFiles/cgi.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cgi.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cgi.dir/flags.make

CMakeFiles/cgi.dir/cgi.o: CMakeFiles/cgi.dir/flags.make
CMakeFiles/cgi.dir/cgi.o: ../cgi.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/linux/cm/cgi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cgi.dir/cgi.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cgi.dir/cgi.o -c /home/linux/cm/cgi/cgi.cc

CMakeFiles/cgi.dir/cgi.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgi.dir/cgi.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/linux/cm/cgi/cgi.cc > CMakeFiles/cgi.dir/cgi.i

CMakeFiles/cgi.dir/cgi.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgi.dir/cgi.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/linux/cm/cgi/cgi.cc -o CMakeFiles/cgi.dir/cgi.s

CMakeFiles/cgi.dir/cgi.o.requires:

.PHONY : CMakeFiles/cgi.dir/cgi.o.requires

CMakeFiles/cgi.dir/cgi.o.provides: CMakeFiles/cgi.dir/cgi.o.requires
	$(MAKE) -f CMakeFiles/cgi.dir/build.make CMakeFiles/cgi.dir/cgi.o.provides.build
.PHONY : CMakeFiles/cgi.dir/cgi.o.provides

CMakeFiles/cgi.dir/cgi.o.provides.build: CMakeFiles/cgi.dir/cgi.o


# Object files for target cgi
cgi_OBJECTS = \
"CMakeFiles/cgi.dir/cgi.o"

# External object files for target cgi
cgi_EXTERNAL_OBJECTS =

cgi: CMakeFiles/cgi.dir/cgi.o
cgi: CMakeFiles/cgi.dir/build.make
cgi: CMakeFiles/cgi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/linux/cm/cgi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cgi"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cgi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cgi.dir/build: cgi

.PHONY : CMakeFiles/cgi.dir/build

CMakeFiles/cgi.dir/requires: CMakeFiles/cgi.dir/cgi.o.requires

.PHONY : CMakeFiles/cgi.dir/requires

CMakeFiles/cgi.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cgi.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cgi.dir/clean

CMakeFiles/cgi.dir/depend:
	cd /home/linux/cm/cgi/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/linux/cm/cgi /home/linux/cm/cgi /home/linux/cm/cgi/build /home/linux/cm/cgi/build /home/linux/cm/cgi/build/CMakeFiles/cgi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cgi.dir/depend

