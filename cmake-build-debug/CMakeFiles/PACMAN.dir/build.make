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
CMAKE_COMMAND = /home/reza/clion-2017.2.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/reza/clion-2017.2.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/reza/CLionProjects/PACMAN

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/reza/CLionProjects/PACMAN/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/PACMAN.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PACMAN.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PACMAN.dir/flags.make

CMakeFiles/PACMAN.dir/src/graphics.c.o: CMakeFiles/PACMAN.dir/flags.make
CMakeFiles/PACMAN.dir/src/graphics.c.o: ../src/graphics.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/reza/CLionProjects/PACMAN/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/PACMAN.dir/src/graphics.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/PACMAN.dir/src/graphics.c.o   -c /home/reza/CLionProjects/PACMAN/src/graphics.c

CMakeFiles/PACMAN.dir/src/graphics.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/PACMAN.dir/src/graphics.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/reza/CLionProjects/PACMAN/src/graphics.c > CMakeFiles/PACMAN.dir/src/graphics.c.i

CMakeFiles/PACMAN.dir/src/graphics.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/PACMAN.dir/src/graphics.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/reza/CLionProjects/PACMAN/src/graphics.c -o CMakeFiles/PACMAN.dir/src/graphics.c.s

CMakeFiles/PACMAN.dir/src/graphics.c.o.requires:

.PHONY : CMakeFiles/PACMAN.dir/src/graphics.c.o.requires

CMakeFiles/PACMAN.dir/src/graphics.c.o.provides: CMakeFiles/PACMAN.dir/src/graphics.c.o.requires
	$(MAKE) -f CMakeFiles/PACMAN.dir/build.make CMakeFiles/PACMAN.dir/src/graphics.c.o.provides.build
.PHONY : CMakeFiles/PACMAN.dir/src/graphics.c.o.provides

CMakeFiles/PACMAN.dir/src/graphics.c.o.provides.build: CMakeFiles/PACMAN.dir/src/graphics.c.o


CMakeFiles/PACMAN.dir/src/physics.c.o: CMakeFiles/PACMAN.dir/flags.make
CMakeFiles/PACMAN.dir/src/physics.c.o: ../src/physics.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/reza/CLionProjects/PACMAN/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/PACMAN.dir/src/physics.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/PACMAN.dir/src/physics.c.o   -c /home/reza/CLionProjects/PACMAN/src/physics.c

CMakeFiles/PACMAN.dir/src/physics.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/PACMAN.dir/src/physics.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/reza/CLionProjects/PACMAN/src/physics.c > CMakeFiles/PACMAN.dir/src/physics.c.i

CMakeFiles/PACMAN.dir/src/physics.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/PACMAN.dir/src/physics.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/reza/CLionProjects/PACMAN/src/physics.c -o CMakeFiles/PACMAN.dir/src/physics.c.s

CMakeFiles/PACMAN.dir/src/physics.c.o.requires:

.PHONY : CMakeFiles/PACMAN.dir/src/physics.c.o.requires

CMakeFiles/PACMAN.dir/src/physics.c.o.provides: CMakeFiles/PACMAN.dir/src/physics.c.o.requires
	$(MAKE) -f CMakeFiles/PACMAN.dir/build.make CMakeFiles/PACMAN.dir/src/physics.c.o.provides.build
.PHONY : CMakeFiles/PACMAN.dir/src/physics.c.o.provides

CMakeFiles/PACMAN.dir/src/physics.c.o.provides.build: CMakeFiles/PACMAN.dir/src/physics.c.o


CMakeFiles/PACMAN.dir/src/game.c.o: CMakeFiles/PACMAN.dir/flags.make
CMakeFiles/PACMAN.dir/src/game.c.o: ../src/game.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/reza/CLionProjects/PACMAN/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/PACMAN.dir/src/game.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/PACMAN.dir/src/game.c.o   -c /home/reza/CLionProjects/PACMAN/src/game.c

CMakeFiles/PACMAN.dir/src/game.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/PACMAN.dir/src/game.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/reza/CLionProjects/PACMAN/src/game.c > CMakeFiles/PACMAN.dir/src/game.c.i

CMakeFiles/PACMAN.dir/src/game.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/PACMAN.dir/src/game.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/reza/CLionProjects/PACMAN/src/game.c -o CMakeFiles/PACMAN.dir/src/game.c.s

CMakeFiles/PACMAN.dir/src/game.c.o.requires:

.PHONY : CMakeFiles/PACMAN.dir/src/game.c.o.requires

CMakeFiles/PACMAN.dir/src/game.c.o.provides: CMakeFiles/PACMAN.dir/src/game.c.o.requires
	$(MAKE) -f CMakeFiles/PACMAN.dir/build.make CMakeFiles/PACMAN.dir/src/game.c.o.provides.build
.PHONY : CMakeFiles/PACMAN.dir/src/game.c.o.provides

CMakeFiles/PACMAN.dir/src/game.c.o.provides.build: CMakeFiles/PACMAN.dir/src/game.c.o


CMakeFiles/PACMAN.dir/main.c.o: CMakeFiles/PACMAN.dir/flags.make
CMakeFiles/PACMAN.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/reza/CLionProjects/PACMAN/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/PACMAN.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/PACMAN.dir/main.c.o   -c /home/reza/CLionProjects/PACMAN/main.c

CMakeFiles/PACMAN.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/PACMAN.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/reza/CLionProjects/PACMAN/main.c > CMakeFiles/PACMAN.dir/main.c.i

CMakeFiles/PACMAN.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/PACMAN.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/reza/CLionProjects/PACMAN/main.c -o CMakeFiles/PACMAN.dir/main.c.s

CMakeFiles/PACMAN.dir/main.c.o.requires:

.PHONY : CMakeFiles/PACMAN.dir/main.c.o.requires

CMakeFiles/PACMAN.dir/main.c.o.provides: CMakeFiles/PACMAN.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/PACMAN.dir/build.make CMakeFiles/PACMAN.dir/main.c.o.provides.build
.PHONY : CMakeFiles/PACMAN.dir/main.c.o.provides

CMakeFiles/PACMAN.dir/main.c.o.provides.build: CMakeFiles/PACMAN.dir/main.c.o


# Object files for target PACMAN
PACMAN_OBJECTS = \
"CMakeFiles/PACMAN.dir/src/graphics.c.o" \
"CMakeFiles/PACMAN.dir/src/physics.c.o" \
"CMakeFiles/PACMAN.dir/src/game.c.o" \
"CMakeFiles/PACMAN.dir/main.c.o"

# External object files for target PACMAN
PACMAN_EXTERNAL_OBJECTS =

PACMAN: CMakeFiles/PACMAN.dir/src/graphics.c.o
PACMAN: CMakeFiles/PACMAN.dir/src/physics.c.o
PACMAN: CMakeFiles/PACMAN.dir/src/game.c.o
PACMAN: CMakeFiles/PACMAN.dir/main.c.o
PACMAN: CMakeFiles/PACMAN.dir/build.make
PACMAN: CMakeFiles/PACMAN.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/reza/CLionProjects/PACMAN/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable PACMAN"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PACMAN.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PACMAN.dir/build: PACMAN

.PHONY : CMakeFiles/PACMAN.dir/build

CMakeFiles/PACMAN.dir/requires: CMakeFiles/PACMAN.dir/src/graphics.c.o.requires
CMakeFiles/PACMAN.dir/requires: CMakeFiles/PACMAN.dir/src/physics.c.o.requires
CMakeFiles/PACMAN.dir/requires: CMakeFiles/PACMAN.dir/src/game.c.o.requires
CMakeFiles/PACMAN.dir/requires: CMakeFiles/PACMAN.dir/main.c.o.requires

.PHONY : CMakeFiles/PACMAN.dir/requires

CMakeFiles/PACMAN.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PACMAN.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PACMAN.dir/clean

CMakeFiles/PACMAN.dir/depend:
	cd /home/reza/CLionProjects/PACMAN/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/reza/CLionProjects/PACMAN /home/reza/CLionProjects/PACMAN /home/reza/CLionProjects/PACMAN/cmake-build-debug /home/reza/CLionProjects/PACMAN/cmake-build-debug /home/reza/CLionProjects/PACMAN/cmake-build-debug/CMakeFiles/PACMAN.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PACMAN.dir/depend

