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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jenifer.santos/sistemas-operacionais/lab01-hello-world

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jenifer.santos/sistemas-operacionais/lab01-hello-world/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/sistemas-operacionais.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/sistemas-operacionais.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sistemas-operacionais.dir/flags.make

CMakeFiles/sistemas-operacionais.dir/HelloWorld.c.o: CMakeFiles/sistemas-operacionais.dir/flags.make
CMakeFiles/sistemas-operacionais.dir/HelloWorld.c.o: ../HelloWorld.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jenifer.santos/sistemas-operacionais/lab01-hello-world/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/sistemas-operacionais.dir/HelloWorld.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sistemas-operacionais.dir/HelloWorld.c.o -c /Users/jenifer.santos/sistemas-operacionais/lab01-hello-world/HelloWorld.c

CMakeFiles/sistemas-operacionais.dir/HelloWorld.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sistemas-operacionais.dir/HelloWorld.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/jenifer.santos/sistemas-operacionais/lab01-hello-world/HelloWorld.c > CMakeFiles/sistemas-operacionais.dir/HelloWorld.c.i

CMakeFiles/sistemas-operacionais.dir/HelloWorld.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sistemas-operacionais.dir/HelloWorld.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/jenifer.santos/sistemas-operacionais/lab01-hello-world/HelloWorld.c -o CMakeFiles/sistemas-operacionais.dir/HelloWorld.c.s

# Object files for target sistemas-operacionais
sistemas__operacionais_OBJECTS = \
"CMakeFiles/sistemas-operacionais.dir/HelloWorld.c.o"

# External object files for target sistemas-operacionais
sistemas__operacionais_EXTERNAL_OBJECTS =

sistemas-operacionais: CMakeFiles/sistemas-operacionais.dir/HelloWorld.c.o
sistemas-operacionais: CMakeFiles/sistemas-operacionais.dir/build.make
sistemas-operacionais: CMakeFiles/sistemas-operacionais.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jenifer.santos/sistemas-operacionais/lab01-hello-world/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable sistemas-operacionais"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sistemas-operacionais.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sistemas-operacionais.dir/build: sistemas-operacionais
.PHONY : CMakeFiles/sistemas-operacionais.dir/build

CMakeFiles/sistemas-operacionais.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sistemas-operacionais.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sistemas-operacionais.dir/clean

CMakeFiles/sistemas-operacionais.dir/depend:
	cd /Users/jenifer.santos/sistemas-operacionais/lab01-hello-world/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jenifer.santos/sistemas-operacionais/lab01-hello-world /Users/jenifer.santos/sistemas-operacionais/lab01-hello-world /Users/jenifer.santos/sistemas-operacionais/lab01-hello-world/cmake-build-debug /Users/jenifer.santos/sistemas-operacionais/lab01-hello-world/cmake-build-debug /Users/jenifer.santos/sistemas-operacionais/lab01-hello-world/cmake-build-debug/CMakeFiles/sistemas-operacionais.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sistemas-operacionais.dir/depend

