# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /snap/clion/73/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/73/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/striker/CLionProjects/Juegos/Juego1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/striker/CLionProjects/Juegos/Juego1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Juego1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Juego1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Juego1.dir/flags.make

CMakeFiles/Juego1.dir/main.cpp.o: CMakeFiles/Juego1.dir/flags.make
CMakeFiles/Juego1.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/striker/CLionProjects/Juegos/Juego1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Juego1.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Juego1.dir/main.cpp.o -c /home/striker/CLionProjects/Juegos/Juego1/main.cpp

CMakeFiles/Juego1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Juego1.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/striker/CLionProjects/Juegos/Juego1/main.cpp > CMakeFiles/Juego1.dir/main.cpp.i

CMakeFiles/Juego1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Juego1.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/striker/CLionProjects/Juegos/Juego1/main.cpp -o CMakeFiles/Juego1.dir/main.cpp.s

# Object files for target Juego1
Juego1_OBJECTS = \
"CMakeFiles/Juego1.dir/main.cpp.o"

# External object files for target Juego1
Juego1_EXTERNAL_OBJECTS =

Juego1: CMakeFiles/Juego1.dir/main.cpp.o
Juego1: CMakeFiles/Juego1.dir/build.make
Juego1: /usr/lib/x86_64-linux-gnu/libOpenGL.so
Juego1: /usr/lib/x86_64-linux-gnu/libGLX.so
Juego1: /usr/lib/x86_64-linux-gnu/libGLU.so
Juego1: /usr/lib/x86_64-linux-gnu/libglut.so
Juego1: /usr/lib/x86_64-linux-gnu/libXi.so
Juego1: /usr/lib/x86_64-linux-gnu/libGLEW.so
Juego1: CMakeFiles/Juego1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/striker/CLionProjects/Juegos/Juego1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Juego1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Juego1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Juego1.dir/build: Juego1

.PHONY : CMakeFiles/Juego1.dir/build

CMakeFiles/Juego1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Juego1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Juego1.dir/clean

CMakeFiles/Juego1.dir/depend:
	cd /home/striker/CLionProjects/Juegos/Juego1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/striker/CLionProjects/Juegos/Juego1 /home/striker/CLionProjects/Juegos/Juego1 /home/striker/CLionProjects/Juegos/Juego1/cmake-build-debug /home/striker/CLionProjects/Juegos/Juego1/cmake-build-debug /home/striker/CLionProjects/Juegos/Juego1/cmake-build-debug/CMakeFiles/Juego1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Juego1.dir/depend

