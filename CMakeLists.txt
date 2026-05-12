cmake_minimum_required(VERSION 3.15)
project(VerletEngine)

add_subdirectory(external/raylib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/physics/Solver.cpp
    src/physics/constraints/BoundsConstraint.cpp
    src/physics/constraints/DistanceConstraint.cpp
    src/render/Renderer.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
