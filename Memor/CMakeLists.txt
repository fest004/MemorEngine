cmake_minimum_required(VERSION 3.0)
project(FloatingBall)

set(CMAKE_CXX_STANDARD 11)

# Find the SFML library
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add the executable
add_executable(FloatingBall main.cpp)

# Link the SFML libraries
target_link_libraries(FloatingBall sfml-graphics sfml-window sfml-system)

