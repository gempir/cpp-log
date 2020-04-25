cmake_minimum_required(VERSION 3.10)
project(gempir)

# Enable C++11
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Boost
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS iostreams) 

# Include CPR - make sure you run `git submodule update --init --recursive`
add_subdirectory(cpr)

# Add directories that you can #include
include_directories(${Boost_INCLUDE_DIRS}) 
include_directories(${CPR_INCLUDE_DIRS})
include_directories(src)

link_libraries(stdc++fs)

# Main executable, add other .cpp files here for compilation
add_executable(main
    src/main.cpp
)

# Link CPR
target_link_libraries(main ${Boost_LIBRARIES} ${CPR_LIBRARIES})
