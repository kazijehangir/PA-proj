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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build"

# Include any dependencies generated for this target.
include countStatic/CMakeFiles/CountStaticPass.dir/depend.make

# Include the progress variables for this target.
include countStatic/CMakeFiles/CountStaticPass.dir/progress.make

# Include the compile flags for this target's objects.
include countStatic/CMakeFiles/CountStaticPass.dir/flags.make

countStatic/CMakeFiles/CountStaticPass.dir/CountStaticInstructions.cpp.o: countStatic/CMakeFiles/CountStaticPass.dir/flags.make
countStatic/CMakeFiles/CountStaticPass.dir/CountStaticInstructions.cpp.o: ../countStatic/CountStaticInstructions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object countStatic/CMakeFiles/CountStaticPass.dir/CountStaticInstructions.cpp.o"
	cd "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build/countStatic" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CountStaticPass.dir/CountStaticInstructions.cpp.o -c "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/countStatic/CountStaticInstructions.cpp"

countStatic/CMakeFiles/CountStaticPass.dir/CountStaticInstructions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CountStaticPass.dir/CountStaticInstructions.cpp.i"
	cd "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build/countStatic" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/countStatic/CountStaticInstructions.cpp" > CMakeFiles/CountStaticPass.dir/CountStaticInstructions.cpp.i

countStatic/CMakeFiles/CountStaticPass.dir/CountStaticInstructions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CountStaticPass.dir/CountStaticInstructions.cpp.s"
	cd "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build/countStatic" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/countStatic/CountStaticInstructions.cpp" -o CMakeFiles/CountStaticPass.dir/CountStaticInstructions.cpp.s

countStatic/CMakeFiles/CountStaticPass.dir/CountStaticInstructions.cpp.o.requires:

.PHONY : countStatic/CMakeFiles/CountStaticPass.dir/CountStaticInstructions.cpp.o.requires

countStatic/CMakeFiles/CountStaticPass.dir/CountStaticInstructions.cpp.o.provides: countStatic/CMakeFiles/CountStaticPass.dir/CountStaticInstructions.cpp.o.requires
	$(MAKE) -f countStatic/CMakeFiles/CountStaticPass.dir/build.make countStatic/CMakeFiles/CountStaticPass.dir/CountStaticInstructions.cpp.o.provides.build
.PHONY : countStatic/CMakeFiles/CountStaticPass.dir/CountStaticInstructions.cpp.o.provides

countStatic/CMakeFiles/CountStaticPass.dir/CountStaticInstructions.cpp.o.provides.build: countStatic/CMakeFiles/CountStaticPass.dir/CountStaticInstructions.cpp.o


# Object files for target CountStaticPass
CountStaticPass_OBJECTS = \
"CMakeFiles/CountStaticPass.dir/CountStaticInstructions.cpp.o"

# External object files for target CountStaticPass
CountStaticPass_EXTERNAL_OBJECTS =

countStatic/libCountStaticPass.so: countStatic/CMakeFiles/CountStaticPass.dir/CountStaticInstructions.cpp.o
countStatic/libCountStaticPass.so: countStatic/CMakeFiles/CountStaticPass.dir/build.make
countStatic/libCountStaticPass.so: countStatic/CMakeFiles/CountStaticPass.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module libCountStaticPass.so"
	cd "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build/countStatic" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CountStaticPass.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
countStatic/CMakeFiles/CountStaticPass.dir/build: countStatic/libCountStaticPass.so

.PHONY : countStatic/CMakeFiles/CountStaticPass.dir/build

countStatic/CMakeFiles/CountStaticPass.dir/requires: countStatic/CMakeFiles/CountStaticPass.dir/CountStaticInstructions.cpp.o.requires

.PHONY : countStatic/CMakeFiles/CountStaticPass.dir/requires

countStatic/CMakeFiles/CountStaticPass.dir/clean:
	cd "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build/countStatic" && $(CMAKE_COMMAND) -P CMakeFiles/CountStaticPass.dir/cmake_clean.cmake
.PHONY : countStatic/CMakeFiles/CountStaticPass.dir/clean

countStatic/CMakeFiles/CountStaticPass.dir/depend:
	cd "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations" "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/countStatic" "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build" "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build/countStatic" "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build/countStatic/CMakeFiles/CountStaticPass.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : countStatic/CMakeFiles/CountStaticPass.dir/depend

