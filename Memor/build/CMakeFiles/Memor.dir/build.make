# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/ubuntu/dev/cpp/MemorEngine/Memor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/dev/cpp/MemorEngine/Memor/build

# Include any dependencies generated for this target.
include CMakeFiles/Memor.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Memor.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Memor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Memor.dir/flags.make

CMakeFiles/Memor.dir/main.cpp.o: CMakeFiles/Memor.dir/flags.make
CMakeFiles/Memor.dir/main.cpp.o: ../main.cpp
CMakeFiles/Memor.dir/main.cpp.o: CMakeFiles/Memor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/dev/cpp/MemorEngine/Memor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Memor.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Memor.dir/main.cpp.o -MF CMakeFiles/Memor.dir/main.cpp.o.d -o CMakeFiles/Memor.dir/main.cpp.o -c /home/ubuntu/dev/cpp/MemorEngine/Memor/main.cpp

CMakeFiles/Memor.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Memor.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/dev/cpp/MemorEngine/Memor/main.cpp > CMakeFiles/Memor.dir/main.cpp.i

CMakeFiles/Memor.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Memor.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/dev/cpp/MemorEngine/Memor/main.cpp -o CMakeFiles/Memor.dir/main.cpp.s

CMakeFiles/Memor.dir/src/action.cpp.o: CMakeFiles/Memor.dir/flags.make
CMakeFiles/Memor.dir/src/action.cpp.o: ../src/action.cpp
CMakeFiles/Memor.dir/src/action.cpp.o: CMakeFiles/Memor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/dev/cpp/MemorEngine/Memor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Memor.dir/src/action.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Memor.dir/src/action.cpp.o -MF CMakeFiles/Memor.dir/src/action.cpp.o.d -o CMakeFiles/Memor.dir/src/action.cpp.o -c /home/ubuntu/dev/cpp/MemorEngine/Memor/src/action.cpp

CMakeFiles/Memor.dir/src/action.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Memor.dir/src/action.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/dev/cpp/MemorEngine/Memor/src/action.cpp > CMakeFiles/Memor.dir/src/action.cpp.i

CMakeFiles/Memor.dir/src/action.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Memor.dir/src/action.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/dev/cpp/MemorEngine/Memor/src/action.cpp -o CMakeFiles/Memor.dir/src/action.cpp.s

CMakeFiles/Memor.dir/src/math/mat4.cpp.o: CMakeFiles/Memor.dir/flags.make
CMakeFiles/Memor.dir/src/math/mat4.cpp.o: ../src/math/mat4.cpp
CMakeFiles/Memor.dir/src/math/mat4.cpp.o: CMakeFiles/Memor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/dev/cpp/MemorEngine/Memor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Memor.dir/src/math/mat4.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Memor.dir/src/math/mat4.cpp.o -MF CMakeFiles/Memor.dir/src/math/mat4.cpp.o.d -o CMakeFiles/Memor.dir/src/math/mat4.cpp.o -c /home/ubuntu/dev/cpp/MemorEngine/Memor/src/math/mat4.cpp

CMakeFiles/Memor.dir/src/math/mat4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Memor.dir/src/math/mat4.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/dev/cpp/MemorEngine/Memor/src/math/mat4.cpp > CMakeFiles/Memor.dir/src/math/mat4.cpp.i

CMakeFiles/Memor.dir/src/math/mat4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Memor.dir/src/math/mat4.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/dev/cpp/MemorEngine/Memor/src/math/mat4.cpp -o CMakeFiles/Memor.dir/src/math/mat4.cpp.s

CMakeFiles/Memor.dir/src/math/vec2.cpp.o: CMakeFiles/Memor.dir/flags.make
CMakeFiles/Memor.dir/src/math/vec2.cpp.o: ../src/math/vec2.cpp
CMakeFiles/Memor.dir/src/math/vec2.cpp.o: CMakeFiles/Memor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/dev/cpp/MemorEngine/Memor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Memor.dir/src/math/vec2.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Memor.dir/src/math/vec2.cpp.o -MF CMakeFiles/Memor.dir/src/math/vec2.cpp.o.d -o CMakeFiles/Memor.dir/src/math/vec2.cpp.o -c /home/ubuntu/dev/cpp/MemorEngine/Memor/src/math/vec2.cpp

CMakeFiles/Memor.dir/src/math/vec2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Memor.dir/src/math/vec2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/dev/cpp/MemorEngine/Memor/src/math/vec2.cpp > CMakeFiles/Memor.dir/src/math/vec2.cpp.i

CMakeFiles/Memor.dir/src/math/vec2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Memor.dir/src/math/vec2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/dev/cpp/MemorEngine/Memor/src/math/vec2.cpp -o CMakeFiles/Memor.dir/src/math/vec2.cpp.s

CMakeFiles/Memor.dir/src/math/vec3.cpp.o: CMakeFiles/Memor.dir/flags.make
CMakeFiles/Memor.dir/src/math/vec3.cpp.o: ../src/math/vec3.cpp
CMakeFiles/Memor.dir/src/math/vec3.cpp.o: CMakeFiles/Memor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/dev/cpp/MemorEngine/Memor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Memor.dir/src/math/vec3.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Memor.dir/src/math/vec3.cpp.o -MF CMakeFiles/Memor.dir/src/math/vec3.cpp.o.d -o CMakeFiles/Memor.dir/src/math/vec3.cpp.o -c /home/ubuntu/dev/cpp/MemorEngine/Memor/src/math/vec3.cpp

CMakeFiles/Memor.dir/src/math/vec3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Memor.dir/src/math/vec3.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/dev/cpp/MemorEngine/Memor/src/math/vec3.cpp > CMakeFiles/Memor.dir/src/math/vec3.cpp.i

CMakeFiles/Memor.dir/src/math/vec3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Memor.dir/src/math/vec3.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/dev/cpp/MemorEngine/Memor/src/math/vec3.cpp -o CMakeFiles/Memor.dir/src/math/vec3.cpp.s

CMakeFiles/Memor.dir/src/math/vec4.cpp.o: CMakeFiles/Memor.dir/flags.make
CMakeFiles/Memor.dir/src/math/vec4.cpp.o: ../src/math/vec4.cpp
CMakeFiles/Memor.dir/src/math/vec4.cpp.o: CMakeFiles/Memor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/dev/cpp/MemorEngine/Memor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Memor.dir/src/math/vec4.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Memor.dir/src/math/vec4.cpp.o -MF CMakeFiles/Memor.dir/src/math/vec4.cpp.o.d -o CMakeFiles/Memor.dir/src/math/vec4.cpp.o -c /home/ubuntu/dev/cpp/MemorEngine/Memor/src/math/vec4.cpp

CMakeFiles/Memor.dir/src/math/vec4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Memor.dir/src/math/vec4.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/dev/cpp/MemorEngine/Memor/src/math/vec4.cpp > CMakeFiles/Memor.dir/src/math/vec4.cpp.i

CMakeFiles/Memor.dir/src/math/vec4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Memor.dir/src/math/vec4.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/dev/cpp/MemorEngine/Memor/src/math/vec4.cpp -o CMakeFiles/Memor.dir/src/math/vec4.cpp.s

CMakeFiles/Memor.dir/src/memor.cpp.o: CMakeFiles/Memor.dir/flags.make
CMakeFiles/Memor.dir/src/memor.cpp.o: ../src/memor.cpp
CMakeFiles/Memor.dir/src/memor.cpp.o: CMakeFiles/Memor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/dev/cpp/MemorEngine/Memor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Memor.dir/src/memor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Memor.dir/src/memor.cpp.o -MF CMakeFiles/Memor.dir/src/memor.cpp.o.d -o CMakeFiles/Memor.dir/src/memor.cpp.o -c /home/ubuntu/dev/cpp/MemorEngine/Memor/src/memor.cpp

CMakeFiles/Memor.dir/src/memor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Memor.dir/src/memor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/dev/cpp/MemorEngine/Memor/src/memor.cpp > CMakeFiles/Memor.dir/src/memor.cpp.i

CMakeFiles/Memor.dir/src/memor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Memor.dir/src/memor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/dev/cpp/MemorEngine/Memor/src/memor.cpp -o CMakeFiles/Memor.dir/src/memor.cpp.s

CMakeFiles/Memor.dir/src/memorlogger/log.cpp.o: CMakeFiles/Memor.dir/flags.make
CMakeFiles/Memor.dir/src/memorlogger/log.cpp.o: ../src/memorlogger/log.cpp
CMakeFiles/Memor.dir/src/memorlogger/log.cpp.o: CMakeFiles/Memor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/dev/cpp/MemorEngine/Memor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Memor.dir/src/memorlogger/log.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Memor.dir/src/memorlogger/log.cpp.o -MF CMakeFiles/Memor.dir/src/memorlogger/log.cpp.o.d -o CMakeFiles/Memor.dir/src/memorlogger/log.cpp.o -c /home/ubuntu/dev/cpp/MemorEngine/Memor/src/memorlogger/log.cpp

CMakeFiles/Memor.dir/src/memorlogger/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Memor.dir/src/memorlogger/log.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/dev/cpp/MemorEngine/Memor/src/memorlogger/log.cpp > CMakeFiles/Memor.dir/src/memorlogger/log.cpp.i

CMakeFiles/Memor.dir/src/memorlogger/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Memor.dir/src/memorlogger/log.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/dev/cpp/MemorEngine/Memor/src/memorlogger/log.cpp -o CMakeFiles/Memor.dir/src/memorlogger/log.cpp.s

CMakeFiles/Memor.dir/src/physics/aabb.cpp.o: CMakeFiles/Memor.dir/flags.make
CMakeFiles/Memor.dir/src/physics/aabb.cpp.o: ../src/physics/aabb.cpp
CMakeFiles/Memor.dir/src/physics/aabb.cpp.o: CMakeFiles/Memor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/dev/cpp/MemorEngine/Memor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/Memor.dir/src/physics/aabb.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Memor.dir/src/physics/aabb.cpp.o -MF CMakeFiles/Memor.dir/src/physics/aabb.cpp.o.d -o CMakeFiles/Memor.dir/src/physics/aabb.cpp.o -c /home/ubuntu/dev/cpp/MemorEngine/Memor/src/physics/aabb.cpp

CMakeFiles/Memor.dir/src/physics/aabb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Memor.dir/src/physics/aabb.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/dev/cpp/MemorEngine/Memor/src/physics/aabb.cpp > CMakeFiles/Memor.dir/src/physics/aabb.cpp.i

CMakeFiles/Memor.dir/src/physics/aabb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Memor.dir/src/physics/aabb.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/dev/cpp/MemorEngine/Memor/src/physics/aabb.cpp -o CMakeFiles/Memor.dir/src/physics/aabb.cpp.s

CMakeFiles/Memor.dir/src/physics/detection.cpp.o: CMakeFiles/Memor.dir/flags.make
CMakeFiles/Memor.dir/src/physics/detection.cpp.o: ../src/physics/detection.cpp
CMakeFiles/Memor.dir/src/physics/detection.cpp.o: CMakeFiles/Memor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/dev/cpp/MemorEngine/Memor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/Memor.dir/src/physics/detection.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Memor.dir/src/physics/detection.cpp.o -MF CMakeFiles/Memor.dir/src/physics/detection.cpp.o.d -o CMakeFiles/Memor.dir/src/physics/detection.cpp.o -c /home/ubuntu/dev/cpp/MemorEngine/Memor/src/physics/detection.cpp

CMakeFiles/Memor.dir/src/physics/detection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Memor.dir/src/physics/detection.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/dev/cpp/MemorEngine/Memor/src/physics/detection.cpp > CMakeFiles/Memor.dir/src/physics/detection.cpp.i

CMakeFiles/Memor.dir/src/physics/detection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Memor.dir/src/physics/detection.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/dev/cpp/MemorEngine/Memor/src/physics/detection.cpp -o CMakeFiles/Memor.dir/src/physics/detection.cpp.s

CMakeFiles/Memor.dir/src/physics/restituion.cpp.o: CMakeFiles/Memor.dir/flags.make
CMakeFiles/Memor.dir/src/physics/restituion.cpp.o: ../src/physics/restituion.cpp
CMakeFiles/Memor.dir/src/physics/restituion.cpp.o: CMakeFiles/Memor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/dev/cpp/MemorEngine/Memor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/Memor.dir/src/physics/restituion.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Memor.dir/src/physics/restituion.cpp.o -MF CMakeFiles/Memor.dir/src/physics/restituion.cpp.o.d -o CMakeFiles/Memor.dir/src/physics/restituion.cpp.o -c /home/ubuntu/dev/cpp/MemorEngine/Memor/src/physics/restituion.cpp

CMakeFiles/Memor.dir/src/physics/restituion.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Memor.dir/src/physics/restituion.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/dev/cpp/MemorEngine/Memor/src/physics/restituion.cpp > CMakeFiles/Memor.dir/src/physics/restituion.cpp.i

CMakeFiles/Memor.dir/src/physics/restituion.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Memor.dir/src/physics/restituion.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/dev/cpp/MemorEngine/Memor/src/physics/restituion.cpp -o CMakeFiles/Memor.dir/src/physics/restituion.cpp.s

CMakeFiles/Memor.dir/src/renderables/animation.cpp.o: CMakeFiles/Memor.dir/flags.make
CMakeFiles/Memor.dir/src/renderables/animation.cpp.o: ../src/renderables/animation.cpp
CMakeFiles/Memor.dir/src/renderables/animation.cpp.o: CMakeFiles/Memor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/dev/cpp/MemorEngine/Memor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/Memor.dir/src/renderables/animation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Memor.dir/src/renderables/animation.cpp.o -MF CMakeFiles/Memor.dir/src/renderables/animation.cpp.o.d -o CMakeFiles/Memor.dir/src/renderables/animation.cpp.o -c /home/ubuntu/dev/cpp/MemorEngine/Memor/src/renderables/animation.cpp

CMakeFiles/Memor.dir/src/renderables/animation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Memor.dir/src/renderables/animation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/dev/cpp/MemorEngine/Memor/src/renderables/animation.cpp > CMakeFiles/Memor.dir/src/renderables/animation.cpp.i

CMakeFiles/Memor.dir/src/renderables/animation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Memor.dir/src/renderables/animation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/dev/cpp/MemorEngine/Memor/src/renderables/animation.cpp -o CMakeFiles/Memor.dir/src/renderables/animation.cpp.s

CMakeFiles/Memor.dir/src/renderables/assets.cpp.o: CMakeFiles/Memor.dir/flags.make
CMakeFiles/Memor.dir/src/renderables/assets.cpp.o: ../src/renderables/assets.cpp
CMakeFiles/Memor.dir/src/renderables/assets.cpp.o: CMakeFiles/Memor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/dev/cpp/MemorEngine/Memor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/Memor.dir/src/renderables/assets.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Memor.dir/src/renderables/assets.cpp.o -MF CMakeFiles/Memor.dir/src/renderables/assets.cpp.o.d -o CMakeFiles/Memor.dir/src/renderables/assets.cpp.o -c /home/ubuntu/dev/cpp/MemorEngine/Memor/src/renderables/assets.cpp

CMakeFiles/Memor.dir/src/renderables/assets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Memor.dir/src/renderables/assets.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/dev/cpp/MemorEngine/Memor/src/renderables/assets.cpp > CMakeFiles/Memor.dir/src/renderables/assets.cpp.i

CMakeFiles/Memor.dir/src/renderables/assets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Memor.dir/src/renderables/assets.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/dev/cpp/MemorEngine/Memor/src/renderables/assets.cpp -o CMakeFiles/Memor.dir/src/renderables/assets.cpp.s

CMakeFiles/Memor.dir/src/scenes/scene.cpp.o: CMakeFiles/Memor.dir/flags.make
CMakeFiles/Memor.dir/src/scenes/scene.cpp.o: ../src/scenes/scene.cpp
CMakeFiles/Memor.dir/src/scenes/scene.cpp.o: CMakeFiles/Memor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/dev/cpp/MemorEngine/Memor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/Memor.dir/src/scenes/scene.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Memor.dir/src/scenes/scene.cpp.o -MF CMakeFiles/Memor.dir/src/scenes/scene.cpp.o.d -o CMakeFiles/Memor.dir/src/scenes/scene.cpp.o -c /home/ubuntu/dev/cpp/MemorEngine/Memor/src/scenes/scene.cpp

CMakeFiles/Memor.dir/src/scenes/scene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Memor.dir/src/scenes/scene.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/dev/cpp/MemorEngine/Memor/src/scenes/scene.cpp > CMakeFiles/Memor.dir/src/scenes/scene.cpp.i

CMakeFiles/Memor.dir/src/scenes/scene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Memor.dir/src/scenes/scene.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/dev/cpp/MemorEngine/Memor/src/scenes/scene.cpp -o CMakeFiles/Memor.dir/src/scenes/scene.cpp.s

CMakeFiles/Memor.dir/src/scenes/startscreen.cpp.o: CMakeFiles/Memor.dir/flags.make
CMakeFiles/Memor.dir/src/scenes/startscreen.cpp.o: ../src/scenes/startscreen.cpp
CMakeFiles/Memor.dir/src/scenes/startscreen.cpp.o: CMakeFiles/Memor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/dev/cpp/MemorEngine/Memor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/Memor.dir/src/scenes/startscreen.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Memor.dir/src/scenes/startscreen.cpp.o -MF CMakeFiles/Memor.dir/src/scenes/startscreen.cpp.o.d -o CMakeFiles/Memor.dir/src/scenes/startscreen.cpp.o -c /home/ubuntu/dev/cpp/MemorEngine/Memor/src/scenes/startscreen.cpp

CMakeFiles/Memor.dir/src/scenes/startscreen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Memor.dir/src/scenes/startscreen.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/dev/cpp/MemorEngine/Memor/src/scenes/startscreen.cpp > CMakeFiles/Memor.dir/src/scenes/startscreen.cpp.i

CMakeFiles/Memor.dir/src/scenes/startscreen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Memor.dir/src/scenes/startscreen.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/dev/cpp/MemorEngine/Memor/src/scenes/startscreen.cpp -o CMakeFiles/Memor.dir/src/scenes/startscreen.cpp.s

# Object files for target Memor
Memor_OBJECTS = \
"CMakeFiles/Memor.dir/main.cpp.o" \
"CMakeFiles/Memor.dir/src/action.cpp.o" \
"CMakeFiles/Memor.dir/src/math/mat4.cpp.o" \
"CMakeFiles/Memor.dir/src/math/vec2.cpp.o" \
"CMakeFiles/Memor.dir/src/math/vec3.cpp.o" \
"CMakeFiles/Memor.dir/src/math/vec4.cpp.o" \
"CMakeFiles/Memor.dir/src/memor.cpp.o" \
"CMakeFiles/Memor.dir/src/memorlogger/log.cpp.o" \
"CMakeFiles/Memor.dir/src/physics/aabb.cpp.o" \
"CMakeFiles/Memor.dir/src/physics/detection.cpp.o" \
"CMakeFiles/Memor.dir/src/physics/restituion.cpp.o" \
"CMakeFiles/Memor.dir/src/renderables/animation.cpp.o" \
"CMakeFiles/Memor.dir/src/renderables/assets.cpp.o" \
"CMakeFiles/Memor.dir/src/scenes/scene.cpp.o" \
"CMakeFiles/Memor.dir/src/scenes/startscreen.cpp.o"

# External object files for target Memor
Memor_EXTERNAL_OBJECTS =

Memor: CMakeFiles/Memor.dir/main.cpp.o
Memor: CMakeFiles/Memor.dir/src/action.cpp.o
Memor: CMakeFiles/Memor.dir/src/math/mat4.cpp.o
Memor: CMakeFiles/Memor.dir/src/math/vec2.cpp.o
Memor: CMakeFiles/Memor.dir/src/math/vec3.cpp.o
Memor: CMakeFiles/Memor.dir/src/math/vec4.cpp.o
Memor: CMakeFiles/Memor.dir/src/memor.cpp.o
Memor: CMakeFiles/Memor.dir/src/memorlogger/log.cpp.o
Memor: CMakeFiles/Memor.dir/src/physics/aabb.cpp.o
Memor: CMakeFiles/Memor.dir/src/physics/detection.cpp.o
Memor: CMakeFiles/Memor.dir/src/physics/restituion.cpp.o
Memor: CMakeFiles/Memor.dir/src/renderables/animation.cpp.o
Memor: CMakeFiles/Memor.dir/src/renderables/assets.cpp.o
Memor: CMakeFiles/Memor.dir/src/scenes/scene.cpp.o
Memor: CMakeFiles/Memor.dir/src/scenes/startscreen.cpp.o
Memor: CMakeFiles/Memor.dir/build.make
Memor: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so.2.5.1
Memor: /usr/lib/x86_64-linux-gnu/libsfml-window.so.2.5.1
Memor: /usr/lib/x86_64-linux-gnu/libsfml-audio.so.2.5.1
Memor: /usr/lib/x86_64-linux-gnu/libspdlog.so.1.9.2
Memor: libLogger.so
Memor: /usr/lib/x86_64-linux-gnu/libsfml-system.so.2.5.1
Memor: /usr/lib/x86_64-linux-gnu/libfmt.so.8.1.1
Memor: CMakeFiles/Memor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/dev/cpp/MemorEngine/Memor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking CXX executable Memor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Memor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Memor.dir/build: Memor
.PHONY : CMakeFiles/Memor.dir/build

CMakeFiles/Memor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Memor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Memor.dir/clean

CMakeFiles/Memor.dir/depend:
	cd /home/ubuntu/dev/cpp/MemorEngine/Memor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/dev/cpp/MemorEngine/Memor /home/ubuntu/dev/cpp/MemorEngine/Memor /home/ubuntu/dev/cpp/MemorEngine/Memor/build /home/ubuntu/dev/cpp/MemorEngine/Memor/build /home/ubuntu/dev/cpp/MemorEngine/Memor/build/CMakeFiles/Memor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Memor.dir/depend

