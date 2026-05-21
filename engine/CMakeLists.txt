set(VERLET_IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)

add_library(
    imgui
    STATIC

    ${VERLET_IMGUI_DIR}/imgui.cpp
    ${VERLET_IMGUI_DIR}/imgui_demo.cpp
    ${VERLET_IMGUI_DIR}/imgui_draw.cpp
    ${VERLET_IMGUI_DIR}/imgui_tables.cpp
    ${VERLET_IMGUI_DIR}/imgui_widgets.cpp
    ${VERLET_IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${VERLET_IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(
    imgui
    SYSTEM
    PUBLIC
        ${VERLET_IMGUI_DIR}
        ${VERLET_IMGUI_DIR}/backends
        ${CMAKE_SOURCE_DIR}/external/raylib/src/external/glfw/include
)

add_library(
    engine
    STATIC
    
    physics/Solver.cpp
    physics/constraints/BoundsConstraint.cpp
    physics/constraints/DistanceConstraint.cpp
    
    app/Application.cpp
    
    render/Renderer.cpp
    
    modules/chain/Chain.cpp
)

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(engine PUBLIC raylib imgui)
