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
include branchBias/CMakeFiles/BranchBiasPass.dir/depend.make

# Include the progress variables for this target.
include branchBias/CMakeFiles/BranchBiasPass.dir/progress.make

# Include the compile flags for this target's objects.
include branchBias/CMakeFiles/BranchBiasPass.dir/flags.make

branchBias/CMakeFiles/BranchBiasPass.dir/BranchBias.cpp.o: branchBias/CMakeFiles/BranchBiasPass.dir/flags.make
branchBias/CMakeFiles/BranchBiasPass.dir/BranchBias.cpp.o: ../branchBias/BranchBias.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object branchBias/CMakeFiles/BranchBiasPass.dir/BranchBias.cpp.o"
	cd "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build/branchBias" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BranchBiasPass.dir/BranchBias.cpp.o -c "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/branchBias/BranchBias.cpp"

branchBias/CMakeFiles/BranchBiasPass.dir/BranchBias.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BranchBiasPass.dir/BranchBias.cpp.i"
	cd "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build/branchBias" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/branchBias/BranchBias.cpp" > CMakeFiles/BranchBiasPass.dir/BranchBias.cpp.i

branchBias/CMakeFiles/BranchBiasPass.dir/BranchBias.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BranchBiasPass.dir/BranchBias.cpp.s"
	cd "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build/branchBias" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/branchBias/BranchBias.cpp" -o CMakeFiles/BranchBiasPass.dir/BranchBias.cpp.s

branchBias/CMakeFiles/BranchBiasPass.dir/BranchBias.cpp.o.requires:

.PHONY : branchBias/CMakeFiles/BranchBiasPass.dir/BranchBias.cpp.o.requires

branchBias/CMakeFiles/BranchBiasPass.dir/BranchBias.cpp.o.provides: branchBias/CMakeFiles/BranchBiasPass.dir/BranchBias.cpp.o.requires
	$(MAKE) -f branchBias/CMakeFiles/BranchBiasPass.dir/build.make branchBias/CMakeFiles/BranchBiasPass.dir/BranchBias.cpp.o.provides.build
.PHONY : branchBias/CMakeFiles/BranchBiasPass.dir/BranchBias.cpp.o.provides

branchBias/CMakeFiles/BranchBiasPass.dir/BranchBias.cpp.o.provides.build: branchBias/CMakeFiles/BranchBiasPass.dir/BranchBias.cpp.o


# Object files for target BranchBiasPass
BranchBiasPass_OBJECTS = \
"CMakeFiles/BranchBiasPass.dir/BranchBias.cpp.o"

# External object files for target BranchBiasPass
BranchBiasPass_EXTERNAL_OBJECTS =

branchBias/libBranchBiasPass.so: branchBias/CMakeFiles/BranchBiasPass.dir/BranchBias.cpp.o
branchBias/libBranchBiasPass.so: branchBias/CMakeFiles/BranchBiasPass.dir/build.make
branchBias/libBranchBiasPass.so: branchBias/CMakeFiles/BranchBiasPass.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module libBranchBiasPass.so"
	cd "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build/branchBias" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BranchBiasPass.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
branchBias/CMakeFiles/BranchBiasPass.dir/build: branchBias/libBranchBiasPass.so

.PHONY : branchBias/CMakeFiles/BranchBiasPass.dir/build

branchBias/CMakeFiles/BranchBiasPass.dir/requires: branchBias/CMakeFiles/BranchBiasPass.dir/BranchBias.cpp.o.requires

.PHONY : branchBias/CMakeFiles/BranchBiasPass.dir/requires

branchBias/CMakeFiles/BranchBiasPass.dir/clean:
	cd "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build/branchBias" && $(CMAKE_COMMAND) -P CMakeFiles/BranchBiasPass.dir/cmake_clean.cmake
.PHONY : branchBias/CMakeFiles/BranchBiasPass.dir/clean

branchBias/CMakeFiles/BranchBiasPass.dir/depend:
	cd "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations" "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/branchBias" "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build" "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build/branchBias" "/mnt/OS/LUMS-Current/Fall2017/CS4612 - Program Analysis/Assignment2/transformations/build/branchBias/CMakeFiles/BranchBiasPass.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : branchBias/CMakeFiles/BranchBiasPass.dir/depend

