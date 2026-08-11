add_library(
    engine
    STATIC
    
    physics/Solver.cpp
    physics/constraints/BoundsConstraint.cpp
    physics/constraints/DistanceConstraint.cpp
    
    debug/DebugPanel.cpp

    app/Application.cpp
    
    render/Renderer.cpp
    
    modules/chain/Chain.cpp
)

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(engine PUBLIC raylib PRIVATE rlimgui)
