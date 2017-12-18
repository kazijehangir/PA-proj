cmake_minimum_required(VERSION 3.1)

find_package(LLVM REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

add_subdirectory(markSweep)  # Project.
add_subdirectory(countStatic)  # Part 1.
add_subdirectory(countDynamic)  # Part 2.
add_subdirectory(branchBias)  # Part 3.
