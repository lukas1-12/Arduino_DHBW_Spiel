cmake_minimum_required (VERSION 3.10.2)

project (game_logic VERSION 0.0.2 LANGUAGES CXX)

# Turn on/off the tests
option(BUILD_TESTS "Build the tests" ON)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include dependencies


# Add include directories
find_package(Catch2 3 REQUIRED)     	

# Add libraries
add_library(uni_library STATIC
    logic.cpp)

# Add the executable
add_executable(${PROJECT_NAME} main.cpp)

# Link libraries to the executable
target_link_libraries(${PROJECT_NAME} PRIVATE
    uni_library)

# Include directories for libraries
#target_include_directories(uni_library PUBLIC include)
target_include_directories(uni_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# test helpers			

# Catch2 should output in JUnit format, and output successful tests, too 

# Set path to CMakeLists.txt in test directory
set(TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../test")

set (CATCH2_DEFAULT_PARAMETERS -r junit) 

macro (add_catch2_test) 

set(prefix ADD_CATCH2_TEST) 

set(oneValueArgs TARGET WORKING_DIR) 

cmake_parse_arguments(${prefix} "" "${oneValueArgs}" "" ${ARGN} ) 

if(NOT DEFINED ${prefix}_WORKING_DIR) 

    set(${prefix}_WORKING_DIR ${CMAKE_BINARY_DIR}) 

    endif() 

endmacro(add_catch2_test) 

 

# Add the tests 

if(BUILD_TESTS) 

  enable_testing() 

add_subdirectory(${TEST_DIR} ${CMAKE_BINARY_DIR}/test) 

endif(BUILD_TESTS) 