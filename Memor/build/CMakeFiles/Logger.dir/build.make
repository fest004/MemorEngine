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
CMAKE_SOURCE_DIR = /home/felix/dev/projects/MemorEngine/Memor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/felix/dev/projects/MemorEngine/Memor/build

# Include any dependencies generated for this target.
include CMakeFiles/Logger.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Logger.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Logger.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Logger.dir/flags.make

CMakeFiles/Logger.dir/src/memorlogger/log.cpp.o: CMakeFiles/Logger.dir/flags.make
CMakeFiles/Logger.dir/src/memorlogger/log.cpp.o: /home/felix/dev/projects/MemorEngine/Memor/src/memorlogger/log.cpp
CMakeFiles/Logger.dir/src/memorlogger/log.cpp.o: CMakeFiles/Logger.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/felix/dev/projects/MemorEngine/Memor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Logger.dir/src/memorlogger/log.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Logger.dir/src/memorlogger/log.cpp.o -MF CMakeFiles/Logger.dir/src/memorlogger/log.cpp.o.d -o CMakeFiles/Logger.dir/src/memorlogger/log.cpp.o -c /home/felix/dev/projects/MemorEngine/Memor/src/memorlogger/log.cpp

CMakeFiles/Logger.dir/src/memorlogger/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Logger.dir/src/memorlogger/log.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/felix/dev/projects/MemorEngine/Memor/src/memorlogger/log.cpp > CMakeFiles/Logger.dir/src/memorlogger/log.cpp.i

CMakeFiles/Logger.dir/src/memorlogger/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Logger.dir/src/memorlogger/log.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/felix/dev/projects/MemorEngine/Memor/src/memorlogger/log.cpp -o CMakeFiles/Logger.dir/src/memorlogger/log.cpp.s

# Object files for target Logger
Logger_OBJECTS = \
"CMakeFiles/Logger.dir/src/memorlogger/log.cpp.o"

# External object files for target Logger
Logger_EXTERNAL_OBJECTS =

libLogger.so: CMakeFiles/Logger.dir/src/memorlogger/log.cpp.o
libLogger.so: CMakeFiles/Logger.dir/build.make
libLogger.so: CMakeFiles/Logger.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/felix/dev/projects/MemorEngine/Memor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libLogger.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Logger.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Logger.dir/build: libLogger.so
.PHONY : CMakeFiles/Logger.dir/build

CMakeFiles/Logger.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Logger.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Logger.dir/clean

CMakeFiles/Logger.dir/depend:
	cd /home/felix/dev/projects/MemorEngine/Memor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/felix/dev/projects/MemorEngine/Memor /home/felix/dev/projects/MemorEngine/Memor /home/felix/dev/projects/MemorEngine/Memor/build /home/felix/dev/projects/MemorEngine/Memor/build /home/felix/dev/projects/MemorEngine/Memor/build/CMakeFiles/Logger.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Logger.dir/depend

