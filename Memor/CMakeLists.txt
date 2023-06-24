cmake_minimum_required(VERSION 3.0)
project(Memor)

set(CMAKE_CXX_STANDARD 11)

# Find the SFML library
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

set(SOURCES_DIR src)

file(GLOB_RECURSE SOURCES ${SOURCES_DIR}/*.cpp)

# Add the executable
add_executable(Memor main.cpp ${SOURCES})

# Link the SFML libraries
target_link_libraries(Memor sfml-graphics sfml-window sfml-system)

