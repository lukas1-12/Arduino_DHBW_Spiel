# define the minimum cmake version
cmake_minimum_required(VERSION 3.20)

# define the project name
project(Blackjack VERSION 1.0 LANGUAGES CXX)

# define the c++ standard version
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add some compile options
add_compile_options(-Wall -Wextra -pedantic -O0)

add_library(uni_library STATIC
    src/blackjack.cpp)

target_include_directories(uni_library PUBLIC include)

add_executable(test_main_exec src/main.cpp)

target_include_directories(test_main_exec PRIVATE include)

target_link_libraries(test_main_exec PRIVATE uni_library)