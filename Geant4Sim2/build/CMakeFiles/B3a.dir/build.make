# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_SOURCE_DIR = /home/local1/Documents/B3a

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/local1/Documents/B3a/build

# Utility rule file for B3a.

# Include any custom commands dependencies for this target.
include CMakeFiles/B3a.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/B3a.dir/progress.make

CMakeFiles/B3a: exampleB3a

B3a: CMakeFiles/B3a
B3a: CMakeFiles/B3a.dir/build.make
.PHONY : B3a

# Rule to build all files generated by this target.
CMakeFiles/B3a.dir/build: B3a
.PHONY : CMakeFiles/B3a.dir/build

CMakeFiles/B3a.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/B3a.dir/cmake_clean.cmake
.PHONY : CMakeFiles/B3a.dir/clean

CMakeFiles/B3a.dir/depend:
	cd /home/local1/Documents/B3a/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/local1/Documents/B3a /home/local1/Documents/B3a /home/local1/Documents/B3a/build /home/local1/Documents/B3a/build /home/local1/Documents/B3a/build/CMakeFiles/B3a.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/B3a.dir/depend

