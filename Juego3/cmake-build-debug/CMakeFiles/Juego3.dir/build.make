# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /home/marcopolo/Programas/clion-2018.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/marcopolo/Programas/clion-2018.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/marcopolo/CLionProjects/Juegos/Juego3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marcopolo/CLionProjects/Juegos/Juego3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Juego3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Juego3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Juego3.dir/flags.make

CMakeFiles/Juego3.dir/main.cpp.o: CMakeFiles/Juego3.dir/flags.make
CMakeFiles/Juego3.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcopolo/CLionProjects/Juegos/Juego3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Juego3.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Juego3.dir/main.cpp.o -c /home/marcopolo/CLionProjects/Juegos/Juego3/main.cpp

CMakeFiles/Juego3.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Juego3.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcopolo/CLionProjects/Juegos/Juego3/main.cpp > CMakeFiles/Juego3.dir/main.cpp.i

CMakeFiles/Juego3.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Juego3.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcopolo/CLionProjects/Juegos/Juego3/main.cpp -o CMakeFiles/Juego3.dir/main.cpp.s

# Object files for target Juego3
Juego3_OBJECTS = \
"CMakeFiles/Juego3.dir/main.cpp.o"

# External object files for target Juego3
Juego3_EXTERNAL_OBJECTS =

Juego3: CMakeFiles/Juego3.dir/main.cpp.o
Juego3: CMakeFiles/Juego3.dir/build.make
Juego3: /usr/lib/x86_64-linux-gnu/libOpenGL.so
Juego3: /usr/lib/x86_64-linux-gnu/libGLX.so
Juego3: /usr/lib/x86_64-linux-gnu/libGLU.so
Juego3: /usr/lib/x86_64-linux-gnu/libglut.so
Juego3: /usr/lib/x86_64-linux-gnu/libXi.so
Juego3: /usr/lib/x86_64-linux-gnu/libGLEW.so
Juego3: CMakeFiles/Juego3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marcopolo/CLionProjects/Juegos/Juego3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Juego3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Juego3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Juego3.dir/build: Juego3

.PHONY : CMakeFiles/Juego3.dir/build

CMakeFiles/Juego3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Juego3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Juego3.dir/clean

CMakeFiles/Juego3.dir/depend:
	cd /home/marcopolo/CLionProjects/Juegos/Juego3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marcopolo/CLionProjects/Juegos/Juego3 /home/marcopolo/CLionProjects/Juegos/Juego3 /home/marcopolo/CLionProjects/Juegos/Juego3/cmake-build-debug /home/marcopolo/CLionProjects/Juegos/Juego3/cmake-build-debug /home/marcopolo/CLionProjects/Juegos/Juego3/cmake-build-debug/CMakeFiles/Juego3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Juego3.dir/depend

