cmake_minimum_required(VERSION 3.15)
project(VerletEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/raylib)
add_subdirectory(external/imgui)
add_subdirectory(external/rlImGui)
add_subdirectory(engine)
add_subdirectory(demos/chain)
add_subdirectory(demos/stressTest)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    engine
    chain_demo
    stress_test 
)
