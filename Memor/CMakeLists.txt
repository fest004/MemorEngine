cmake_minimum_required(VERSION 3.0)
project(Memor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

# Find the SFML library
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(spdlog REQUIRED)

set(SOURCES_DIR src)

file(GLOB_RECURSE SOURCES ${SOURCES_DIR}/*.cpp)

add_library(Logger SHARED
    src/memorlogger/log.cpp
    src/memorlogger/log.hpp
    src/memorlogger/logger.hpp
  )

# Add the executable
add_executable(Memor main.cpp ${SOURCES})

# Link the SFML libraries
target_link_libraries(Memor sfml-graphics sfml-window sfml-system spdlog::spdlog Logger)

