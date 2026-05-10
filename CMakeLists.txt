cmake_minimum_required(VERSION 3.15)
project(VerletEngine)

add_subdirectory(external/raylib)

set(CMAKE_C_STANDARD 17)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/physics/Solver.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)