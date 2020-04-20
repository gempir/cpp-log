cmake_minimum_required(VERSION 3.10)
project(gempir)

# Enable C++11
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include CPR - make sure you run `git submodule update --init --recursive`
add_subdirectory(cpr)

# Add directories that you can #include
include_directories(${CPR_INCLUDE_DIRS})
include_directories(src)

# Main executable, add other .cpp files here for compilation
add_executable(main
    src/main.cpp
)

# Link CPR
target_link_libraries(main ${CPR_LIBRARIES})