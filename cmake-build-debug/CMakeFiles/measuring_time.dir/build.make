# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /home/ilya/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/201.4865.10/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/ilya/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/201.4865.10/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ilya/CLionProjects/measuring_time

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ilya/CLionProjects/measuring_time/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/measuring_time.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/measuring_time.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/measuring_time.dir/flags.make

CMakeFiles/measuring_time.dir/main.c.o: CMakeFiles/measuring_time.dir/flags.make
CMakeFiles/measuring_time.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ilya/CLionProjects/measuring_time/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/measuring_time.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/measuring_time.dir/main.c.o   -c /home/ilya/CLionProjects/measuring_time/main.c

CMakeFiles/measuring_time.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/measuring_time.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ilya/CLionProjects/measuring_time/main.c > CMakeFiles/measuring_time.dir/main.c.i

CMakeFiles/measuring_time.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/measuring_time.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ilya/CLionProjects/measuring_time/main.c -o CMakeFiles/measuring_time.dir/main.c.s

# Object files for target measuring_time
measuring_time_OBJECTS = \
"CMakeFiles/measuring_time.dir/main.c.o"

# External object files for target measuring_time
measuring_time_EXTERNAL_OBJECTS =

measuring_time: CMakeFiles/measuring_time.dir/main.c.o
measuring_time: CMakeFiles/measuring_time.dir/build.make
measuring_time: /usr/lib/x86_64-linux-gnu/libmpich.so
measuring_time: CMakeFiles/measuring_time.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ilya/CLionProjects/measuring_time/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable measuring_time"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/measuring_time.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/measuring_time.dir/build: measuring_time

.PHONY : CMakeFiles/measuring_time.dir/build

CMakeFiles/measuring_time.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/measuring_time.dir/cmake_clean.cmake
.PHONY : CMakeFiles/measuring_time.dir/clean

CMakeFiles/measuring_time.dir/depend:
	cd /home/ilya/CLionProjects/measuring_time/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ilya/CLionProjects/measuring_time /home/ilya/CLionProjects/measuring_time /home/ilya/CLionProjects/measuring_time/cmake-build-debug /home/ilya/CLionProjects/measuring_time/cmake-build-debug /home/ilya/CLionProjects/measuring_time/cmake-build-debug/CMakeFiles/measuring_time.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/measuring_time.dir/depend

