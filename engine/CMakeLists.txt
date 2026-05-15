add_library(
    engine
    STATIC
    physics/Solver.cpp
    physics/constraints/BoundsConstraint.cpp
    physics/constraints/DistanceConstraint.cpp
    app/Application.cpp
    render/Renderer.cpp
)

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(engine PUBLIC raylib)
